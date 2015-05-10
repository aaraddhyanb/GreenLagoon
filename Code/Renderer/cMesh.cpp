#include "cMesh.h"
#include "Collision.h"
#include "SpatialPartition.h"

#include <queue>
#define EPSILON 0.02

cs6963::Octree *cs6963::cMesh::octree=NULL;

namespace
{
	// The vertex information that is sent to the display adaptor must match what the vertex shader expects
	D3DVERTEXELEMENT9 s_vertexElements[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 3*sizeof(float), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 3*sizeof(float)+sizeof(DWORD), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{ 0, 3*sizeof(float)+sizeof(DWORD)+ sizeof(D3DXVECTOR2),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		{ 0, 3*sizeof(float)+sizeof(DWORD)+ sizeof(D3DXVECTOR2)+ sizeof(D3DXVECTOR3),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0},
		{ 0, 3*sizeof(float)+sizeof(DWORD)+ sizeof(D3DXVECTOR2)+ sizeof(D3DXVECTOR3)+ sizeof(D3DXVECTOR3),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0},

		D3DDECL_END()
	};


	struct line_vertex
	{

		float x, y, z;
		DWORD color;
	};

}

namespace cs6963
{
	  D3DPRIMITIVETYPE cMesh::primitiveType=D3DPT_TRIANGLELIST;

	 cMesh::cMesh(IDirect3DDevice9 * i_direct3dDevice,IDirect3D9 * i_direct3dInterface,char * i_meshAddress, float i_rotation,D3DXVECTOR3 i_position)
	  {
		 vertexCount=0; 
		 rotation= i_rotation;
		 triangleCount= 0;
		 position=i_position;
		 m_vertexDeclaration= NULL;
		 m_direct3dInterface=i_direct3dInterface;
	     m_direct3dDevice=i_direct3dDevice;

		 m_scene.indexBuffer = NULL;
		 m_scene.vertexBuffer = NULL;

		 meshAddress=i_meshAddress;
	   }

		D3DXVECTOR3 cMesh::GetPosition( void )
		{
			return position;
		}

		float cMesh::GetRotation()
		{
			return rotation;
		}
		void cMesh::SetRotation(float i_rotation)
		{
			rotation=i_rotation;
		}
		void cMesh::SetPosition( const D3DXVECTOR3 &i_position )
		{
               position = i_position;
		}
		void cMesh::SetPosition(float i_positionX, float i_positionY, float i_positionZ )
		{
               position =D3DXVECTOR3( i_positionX, i_positionY, i_positionZ);
		}
		void cMesh::Translate( const D3DXVECTOR3 &i_offset )
		{
               position += i_offset;
		}

		void cMesh::Update()
		{
		   BeginScene();
		}

	void cMesh::LocalizeMesh()
	{
		D3DXVECTOR3 vertPosition=D3DXVECTOR3(vertexData[0].x, vertexData[0].y, vertexData[0].z);
		position=vertPosition;

		vertexData[0].x=0; 
		vertexData[0].y=0; 
		vertexData[0].z=0;

		for(int i=1;i<vertexCount;++i)
		{
			vertexData[i].x=vertexData[i].x -vertPosition.x; 
		    vertexData[i].y=vertexData[i].y -vertPosition.y; 
		    vertexData[i].z=vertexData[i].z -vertPosition.z;
		}

		// Before the vertex buffer can be changed it must be "locked"
		/*{
			unsigned int lockEntireBuffer = 0;
			DWORD useDefaultLockingBehavior = 0;
			HRESULT result = m_scene.vertexBuffer->Lock( lockEntireBuffer, lockEntireBuffer,
				reinterpret_cast<void**>( &vertexData ), useDefaultLockingBehavior );
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to lock the vertex buffer" );
				return;
			}
		}
		// Before the index buffer can be changed it must be "locked"
		unsigned int * indexData;
		{
			unsigned int lockEntireBuffer = 0;
			DWORD useDefaultLockingBehavior = 0;
			HRESULT result = m_scene.indexBuffer->Lock( lockEntireBuffer, lockEntireBuffer,
				reinterpret_cast<void**>( &indexData ), useDefaultLockingBehavior );
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to lock the index buffer" );
				return;
			}
		}

		// The vertex buffer must be "unlocked" before it can be used
		{
			HRESULT result = m_scene.vertexBuffer->Unlock();
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to unlock the vertex buffer" );
				return;
			}
		}
		// The index buffer must be "unlocked" before it can be used
		{
			HRESULT result = m_scene.indexBuffer->Unlock();
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to unlock the index buffer" );
				return;
			}
		}*/
	}

	bool cMesh::positionChanged()
	{
		return playerPosChanged;
	}

	float cMesh::Dot(D3DXVECTOR3 qp, D3DXVECTOR3 n)
	{
		float dot = qp.x*n.x + qp.y*n.y + qp.z*n.z;
		return dot;
	}

	D3DXVECTOR3 cMesh::Cross(D3DXVECTOR3 ab, D3DXVECTOR3 ac)
	{
		D3DXVECTOR3 crossP = D3DXVECTOR3((ab.y*ac.z - ab.z*ac.y) , (ab.z*ac.x - ab.x*ac.z), (ab.x*ac.y - ab.y*ac.x));
		return crossP;
	}

	// Given segment pq and triangle abc, returns whether segment intersects
	// triangle and if so, also returns the barycentric coordinates (u,v,w)
	// of the intersection point
	int cMesh::IntersectSegmentTriangle(D3DXVECTOR3 p, D3DXVECTOR3 q, D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
								 float &u, float &v, float &w, float &t)
	{
		D3DXVECTOR3 ab = b - a;
		D3DXVECTOR3 ac = c - a;
		D3DXVECTOR3 qp = p - q;

		// Compute triangle normal. Can be precalculated or cached if
		// intersecting multiple segments against the same triangle
		D3DXVECTOR3 n = Cross(ab, ac );

		// Compute denominator d. If d <= 0, segment is parallel to or points
		// away from triangle, so exit early
		float d = Dot( qp, n);
		if (d <= 0.0f) return 0;

		// Compute intersection t value of pq with plane of triangle. A ray
		// intersects if 0 <= t. Segment intersects if 0 <= t <= 1. Delay
		// dividing by d until intersection has been found to pierce triangle
		D3DXVECTOR3 ap = p - a;
		t = Dot(ap, n); 
		if (t < 0.0f) return 0;
		if (t > d) return 0; // For segment; exclude this code line for a ray test

		// Compute barycentric coordinate components and test if within bounds
		D3DXVECTOR3 e = Cross(qp, ap);
		v = Dot(ac, e);
		if (v < 0.0f || v > d) return 0;
		w = -Dot(ab, e);
		if (w < 0.0f || v + w > d) return 0;

		// Segment/ray intersects triangle. Perform delayed division and
		// compute the last barycentric coordinate component
		float ood = 1.0f / d;
		t *= ood;
		v *= ood;
		w *= ood;
		u = 1.0f - v - w;
		return 1;
	}


int TestSegmentAABB(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 min, D3DXVECTOR3 max)
{
    D3DXVECTOR3 c = (min + max) * 0.5f;  // Box center-point
    D3DXVECTOR3 e = max - c;              // Box halflength extents
    D3DXVECTOR3 m = (p0 + p1) * 0.5f;        // Segment midpoint
    D3DXVECTOR3 d = p1 - m;                 // Segment halflength vector
    m = m - c;                         // Translate box and segment to origin
    
    // Try world coordinate axes as separating axes
    float adx = abs(d.x);
    if (abs(m.x) > e.x + adx) return 0;
    float ady = abs(d.y);
    if (abs(m.y) > e.y + ady) return 0;
    float adz = abs(d.z);
    if (abs(m.z) > e.z + adz) return 0;

    // Add in an epsilon term to counteract arithmetic errors when segment is
    // (near) parallel to a coordinate axis
    adx += EPSILON;
    ady += EPSILON;
    adz += EPSILON;

    // Try cross products of segment direction vector with coordinate axes
    if (abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady) return 0;
    if (abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx) return 0;
    if (abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return 0;
    
    // No separating axis found; segment must be overlapping AABB
    return 1;
}

void calculateDebugLines(D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	 renderAsLines line;
	 line.color=D3DCOLOR_XRGB (0, 255, 0);

	 //line 1
	 line.vertex=min;
	 Octree::debugLines.push_back(line);
	 line.vertex=D3DXVECTOR3(max.x, min.y, min.z);
	 Octree::debugLines.push_back(line);

	 //line 2
	 line.vertex=D3DXVECTOR3(max.x, min.y, min.z);
	 Octree::debugLines.push_back(line);
	 line.vertex=D3DXVECTOR3(max.x, max.y, min.z);
	 Octree::debugLines.push_back(line);

	 //line 3
	 line.vertex=D3DXVECTOR3(max.x, max.y, min.z);
	 Octree::debugLines.push_back(line);
	 line.vertex=D3DXVECTOR3(min.x, max.y, min.z);
	 Octree::debugLines.push_back(line);

	 //line 4
	 line.vertex=D3DXVECTOR3(min.x, max.y, min.z);
	 Octree::debugLines.push_back(line);
	 line.vertex=min;
	 Octree::debugLines.push_back(line);

	 //line 5
	 line.vertex=min;
	 Octree::debugLines.push_back(line);
	 line.vertex=D3DXVECTOR3(min.x, min.y, max.z);
	 Octree::debugLines.push_back(line);

	  //line 6
	  line.vertex=D3DXVECTOR3(min.x, min.y, max.z);
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(max.x, min.y, max.z);
	  Octree::debugLines.push_back(line);

	  //line 7
	  line.vertex=D3DXVECTOR3(max.x, min.y, max.z);
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(max.x, max.y, max.z);
	  Octree::debugLines.push_back(line);

	  //line 8
	  line.vertex=max;
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(min.x, max.y, max.z);
	  Octree::debugLines.push_back(line);

	   //line 9
	  line.vertex=D3DXVECTOR3(min.x, max.y, max.z);
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(min.x, min.y, max.z);
	  Octree::debugLines.push_back(line);

	   //line 10
	  line.vertex=D3DXVECTOR3(min.x, max.y, max.z);
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(min.x, max.y, min.z);
	  Octree::debugLines.push_back(line);

	   //line 11
	  line.vertex=max;
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(max.x, max.y, min.z);
	  Octree::debugLines.push_back(line);

	   //line 12
	  line.vertex=D3DXVECTOR3(max.x, min.y, max.z);
	  Octree::debugLines.push_back(line);
	  line.vertex=D3DXVECTOR3(max.x, min.y, min.z);
	  Octree::debugLines.push_back(line);
}

void cMesh::createOctTree()
{
	octree=new Octree();
	octree=octree->readFromFile("octree");
}

void cMesh::detectCollision()
{

	 //clear renderAslines buffer
	 Octree::debugLines.clear();

	  //down ray cast with BB
	  D3DXVECTOR3 q=D3DXVECTOR3(position);
	  q.y-=45.f;
		
	 renderAsLines line;
	 line.vertex=position;
	 line.color=D3DCOLOR_XRGB (0, 255, 255);

	 Octree::debugLines.push_back(line);

	 line.vertex=q;
	 Octree::debugLines.push_back(line);

	 vector<triangle> triangleList;


     //BFS on tree
     std::queue< OctNode *> treeNodes;
	 treeNodes.push(octree->getRootNode());

	 while(treeNodes.size())
	 {
		 OctNode * newNode=treeNodes.front();
		 treeNodes.pop();
		 if(TestSegmentAABB( position, q,newNode->lfb, newNode->rbt))
		 { 
			 calculateDebugLines(newNode->lfb, newNode->rbt);
			 treeNodes.empty();
			 for(int j=0;j< newNode->triangleList.size(); ++j)
			 {
				 triangleList.push_back(newNode->triangleList[j]);
			 }
			 for(int i=0;i <8 ; ++i)
			 {
				 if(newNode->child[i]!=nullptr)
			          treeNodes.push(newNode->child[i]);
			 }
		 }
	 }

 
	 //down ray cast
	 bool downCollided=false;
	 for(int i=0; i< triangleList.size() ; ++i)
	 {
		 float u,v,w,t;
		 D3DXVECTOR3 q=D3DXVECTOR3(position);
		 q.y-=45.f;

		 int collisionDetected= IntersectSegmentTriangle(position, q, triangleList[i].tri[0].pos, triangleList[i].tri[1].pos, triangleList[i].tri[2].pos,
                              u,  v, w, t);
		 if((t>=0.f && t<=1.f) || collisionDetected==1)
		 {
			 D3DXVECTOR3 collidedAt=D3DXVECTOR3(u*D3DXVECTOR3(triangleList[i].tri[0].pos) + v*D3DXVECTOR3(triangleList[i].tri[1].pos) + w*D3DXVECTOR3(triangleList[i].tri[2].pos));
			 //D3DXVECTOR3 bounce=D3DXVECTOR3(position);
			 //bounce.y=collidedAt.y+44.9999;
			 position.y+=(1-t)*30;
			 //position=bounce;
			 downCollided=true;
			 break;
		 }
	 }

	 if(!downCollided)
	 {
		  D3DXVECTOR3 gravity=D3DXVECTOR3(position);
		 gravity.y-=20;
		 position=gravity;
	 }


	//-------------------------------------------------------------------------------------
	
	 //forward ray cast
	 triangleList.clear();

     //BFS on tree
	 treeNodes.empty();
	 treeNodes.push(octree->getRootNode());

	  D3DXVECTOR3 q2=D3DXVECTOR3(position);
	  q2.z-=cos(rotation)*20.f;
	  q2.x-=sin(rotation)*20.f;

	   D3DXVECTOR3 cam=D3DXVECTOR3(position);

	   line.vertex=cam;
	   line.color=D3DCOLOR_XRGB (255, 0, 0);

	   Octree::debugLines.push_back(line);

       line.vertex=q2;
	   Octree::debugLines.push_back(line);

	 while(treeNodes.size())
	 {
		 OctNode * newNode=treeNodes.front();
		 treeNodes.pop();
		 if(TestSegmentAABB( position, q2,newNode->lfb, newNode->rbt))
		 {
			 calculateDebugLines(newNode->lfb, newNode->rbt);
			 treeNodes.empty();
			 for(int j=0;j< newNode->triangleList.size(); ++j)
			 {
				 triangleList.push_back(newNode->triangleList[j]);
			 }
			 for(int i=0;i <8 ; ++i)
			 {
				 if(newNode->child[i]!=nullptr)
			          treeNodes.push(newNode->child[i]);
			 }
		 }
	 }

	 bool forwardCollided=false;

	 for(int i=0; i< triangleList.size() ; i++)
	 {
		 float u,v,w,t;
		 D3DXVECTOR3 q=D3DXVECTOR3(position);

		 q.z+=cos(rotation)*20.f;
		 q.x+=sin(rotation)*20.f;
	
		 int collisionDetected= IntersectSegmentTriangle(position, q,triangleList[i].tri[0].pos,triangleList[i].tri[1].pos, triangleList[i].tri[2].pos,
                              u,  v, w, t);
		 if((t>=0.f && t<=1.f) || collisionDetected==1)
		 {
			 D3DXVECTOR3 bounce=D3DXVECTOR3(position);
			 bounce.z-=(1-t)*cos(rotation)*100.f;
		     bounce.x-=(1-t)*sin(rotation)*100.f;
			 position = bounce;
			 forwardCollided=true;
			 break;
		 }

	}

	 //-------------------------------------------------------------------------------------
	
	 //backward ray cast
	 triangleList.clear();

     //BFS on tree
	 treeNodes.empty();
	 treeNodes.push(octree->getRootNode());

	  D3DXVECTOR3 q3=D3DXVECTOR3(position);
	  q3.z-=cos(rotation)*300.f;
	  q3.x-=sin(rotation)*300.f;

	   line.vertex=D3DXVECTOR3(position);

	   line.color=D3DCOLOR_XRGB (255, 255, 0);

	   Octree::debugLines.push_back(line);

       line.vertex=q3;
	   Octree::debugLines.push_back(line);

	 while(treeNodes.size())
	 {
		 OctNode * newNode=treeNodes.front();
		 treeNodes.pop();
		 if(TestSegmentAABB( position, q3,newNode->lfb, newNode->rbt))
		 {
			 calculateDebugLines(newNode->lfb, newNode->rbt);
			 treeNodes.empty();
			 for(int j=0;j< newNode->triangleList.size(); ++j)
			 {
				 triangleList.push_back(newNode->triangleList[j]);
			 }
			 for(int i=0;i <8 ; ++i)
			 {
				 if(newNode->child[i]!=nullptr)
			          treeNodes.push(newNode->child[i]);
			 }
		 }
	 }

	 for(int i=0; i< triangleList.size() ; i++)
	 {
		 float u,v,w,t;
		 D3DXVECTOR3 q=D3DXVECTOR3(position);

		 q.z-=cos(rotation)*300.f;
		 q.x-=sin(rotation)*300.f;
	
		 int collisionDetected= IntersectSegmentTriangle(position, q,triangleList[i].tri[0].pos,triangleList[i].tri[1].pos, triangleList[i].tri[2].pos,
                              u,  v, w, t);
		 if((t>=0.f && t<=1.f) || collisionDetected==1)
		 {
			 cameraPosition=D3DXVECTOR3(position);
			 cameraPosition.z-=(t)*cos(rotation)*250.f;
		     cameraPosition.x-=(t)*sin(rotation)*250.f;
			 cameraPosition.y+=100.f;
			 break;
		 }
		 else
		 {
			 cameraPosition=D3DXVECTOR3(position);
			 cameraPosition.x-= sin(rotation)*300.f;
			 cameraPosition.z-= cos(rotation)*300.f;
			 cameraPosition.y+=100.f;
		 }
	}
 }

// Create a vertex buffer	
bool cMesh::createBuffers()
{
	// Create a vertex buffer
	{
		// A triangle has three vertices
		unsigned int bufferSize = vertexCount * sizeof( s_vertex );
		
		// The usage tells Direct3D how this vertex buffer will be used
		DWORD usage = 0;
		{
			// Our code will only ever write to the buffer
			usage |= D3DUSAGE_WRITEONLY;
			// The type of vertex processing should match what was specified when the device interface was created
			{
				D3DDEVICE_CREATION_PARAMETERS deviceCreationParameters;
				HRESULT result = m_direct3dDevice->GetCreationParameters( &deviceCreationParameters );
				if ( SUCCEEDED( result ) )
				{
					DWORD vertexProcessingType = deviceCreationParameters.BehaviorFlags &
						( D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_SOFTWARE_VERTEXPROCESSING );
					usage |= ( vertexProcessingType != D3DCREATE_SOFTWARE_VERTEXPROCESSING ) ?
						0 : D3DUSAGE_SOFTWAREPROCESSING;
				}
				else
				{
					LogMessage( "Failed to get the device's creation parameters" );
					return false;
				}
			}
		}
		// We will define our own vertex format
		DWORD useSeparateVertexDeclaration = 0;
		// Place the vertex buffer into memory that Direct3D thinks is the most appropriate
		D3DPOOL useDefaultPool = D3DPOOL_DEFAULT;
		HANDLE* notUsed = NULL;

		HRESULT result = m_direct3dDevice->CreateVertexBuffer( bufferSize, usage, useSeparateVertexDeclaration, useDefaultPool,
			&m_scene.vertexBuffer, notUsed );
		if ( FAILED( result ) )
		{
			LogMessage( "Failed to create the vertex buffer" );
			return false;
		}

		{
			unsigned int bufferSize = triangleCount * sizeof( unsigned int );
			D3DFORMAT format = D3DFMT_INDEX32;
			D3DPOOL useDefaultPool = D3DPOOL_DEFAULT;
			HANDLE* notUsed = NULL;

			HRESULT result = m_direct3dDevice->CreateIndexBuffer( bufferSize, usage, format, useDefaultPool,
					&m_scene.indexBuffer, notUsed );
			if ( FAILED( result ) )
			{
					LogMessage( "Failed to create the index buffer" );
					return false;
			}
		}
	}
    return true;
}

void cMesh::setTextureName(std::string i_textureName)
{
	mTextureName=i_textureName;
}

std::string cMesh::getTextureName()
{
	return mTextureName;
}

void cMesh::WireMode(bool status)
{
	if(status)
		 primitiveType = D3DPT_LINELIST;
	else
	 primitiveType=D3DPT_TRIANGLELIST;
}

void cMesh::BeginScene()
{

	HRESULT result; //= m_direct3dDevice->BeginScene();
	//  assert( SUCCEEDED( result ) );		
		{
	       // Bind a specific vertex buffer to the device as a data source
			{
				// There can be multiple streams of data feeding the display adaptor at the same time
				unsigned int streamIndex = 0;
				// It's possible to start streaming data in the middle of a vertex buffer
				unsigned int bufferOffset = 0;
				// The "stride" defines how large a single vertex is in the stream of data
				unsigned int bufferStride = sizeof( s_vertex );
				result = m_direct3dDevice->SetStreamSource( streamIndex, m_scene.vertexBuffer, bufferOffset, bufferStride );
				assert( SUCCEEDED( result ) );
				result = m_direct3dDevice->SetIndices( m_scene.indexBuffer );
				assert( SUCCEEDED( result ) );
			}


			// Render objects from the current streams
			{
				// We are using triangles as the "primitive" type,
				// and we have defined the vertex buffer as a triangle list
				// (meaning that every triangle is defined by three vertices)
				
				// It's possible to start rendering primitives in the middle of the stream
				unsigned int indexOfFirstVertexToRender = 0;
				// We are currently only rendering a single triangle
				unsigned int primitiveCountToRender = triangleCount/3;
				result = m_direct3dDevice->DrawIndexedPrimitive( primitiveType, indexOfFirstVertexToRender, 0, vertexCount, 0 , primitiveCountToRender );
				assert( SUCCEEDED( result ) );
			}

		}
			
		//result = m_direct3dDevice->EndScene();
		//assert( SUCCEEDED( result ) );
}

// Fill the vertex buffer with the triangle's vertices
bool cMesh::fillBuffers(int i_vertexCount, int i_triangleCount, std::ifstream &meshFileReadOnly)
{
		// Before the vertex buffer can be changed it must be "locked"
		{
			unsigned int lockEntireBuffer = 0;
			DWORD useDefaultLockingBehavior = 0;
			HRESULT result = m_scene.vertexBuffer->Lock( lockEntireBuffer, lockEntireBuffer,
				reinterpret_cast<void**>( &vertexData ), useDefaultLockingBehavior );
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to lock the vertex buffer" );
				return false;
			}
		}
		// Before the index buffer can be changed it must be "locked"
		unsigned int * indexData;
		{
			unsigned int lockEntireBuffer = 0;
			DWORD useDefaultLockingBehavior = 0;
			HRESULT result = m_scene.indexBuffer->Lock( lockEntireBuffer, lockEntireBuffer,
				reinterpret_cast<void**>( &indexData ), useDefaultLockingBehavior );
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to lock the index buffer" );
				return false;
			}
		}

		// Fill the vertex buffer
		{

			vertexCount= i_vertexCount;
			triangleCount= i_triangleCount;
				
			for(int i=0;i<vertexCount;i++)
			{
			    meshFileReadOnly.read(reinterpret_cast<char*>(&vertexData[i]), sizeof(vertexData[i]) );
			}


			for(int i=0;i<triangleCount;i++)
			{
			    meshFileReadOnly.read(reinterpret_cast<char*>(&indexData[i]), sizeof(indexData[i]) );
			}
		}

		// The vertex buffer must be "unlocked" before it can be used
		{
			HRESULT result = m_scene.vertexBuffer->Unlock();
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to unlock the vertex buffer" );
				return false;
			}
		}
		// The index buffer must be "unlocked" before it can be used
		{
			HRESULT result = m_scene.indexBuffer->Unlock();
			if ( FAILED( result ) )
			{
				LogMessage( "Failed to unlock the index buffer" );
				return false;
			}
		}
		return true;
}


void cMesh::SetStatic(bool i_status)
{
	isStatic=i_status;
}

bool cMesh::getNature()
{
	return isStatic;
}

bool cMesh::Initialize(IDirect3DDevice9 * i_direct3dDevice,IDirect3D9 * i_direct3dInterface,char * i_meshAddress, float i_rotation,D3DXVECTOR3 i_position,
	                          int i_vertexCount, int i_triangleCount)
{
	isStatic=true;
	vertexCount=0; 
	rotation= i_rotation;
	triangleCount= 0;
	position=i_position;
	m_vertexDeclaration= NULL;
	m_direct3dInterface=i_direct3dInterface;
	m_direct3dDevice=i_direct3dDevice;

	m_scene.indexBuffer = NULL;
	m_scene.vertexBuffer = NULL;

	meshAddress=i_meshAddress;

	vertexCount=i_vertexCount;
	triangleCount=i_triangleCount;



	//Initializing Vertex Declaration
	{

		HRESULT result = m_direct3dDevice->CreateVertexDeclaration( s_vertexElements, &m_vertexDeclaration );
		if ( SUCCEEDED( result ) )
		{
			LogMessage( "Created the vertex declaration" );
			result = m_direct3dDevice->SetVertexDeclaration( m_vertexDeclaration );
			if ( SUCCEEDED( result ) )
			{
				return true;
			}
			else
			{
				LogMessage( "Failed to set the vertex declaration" );
				return false;
			}
		}
		else
		{
			LogMessage( "Failed to create the vertex declaration" );
			return false;
		}
	}

	return true;
}

} //namespace end