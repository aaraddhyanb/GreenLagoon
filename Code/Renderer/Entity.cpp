#include"Entity.h"
#include<map>

struct line_vertex
{
	float x, y, z;
	DWORD color;
};

namespace cs6963
{

std::vector<renderAsLines> Entity::pathFindingLines;

	Entity::Entity(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface)
	{
			 m_direct3dInterface=i_direct3dInterface;
		     m_direct3dDevice=i_direct3dDevice;
	}
	
	void Entity::getEntity(const std::string &i_meshFile, const std::string &i_textureFile, D3DXVECTOR3 i_position,float i_rotation)
	{
					
		meshFile = (char*)malloc( sizeof( char ) *(i_meshFile.length() +1) );
		strcpy( meshFile, i_meshFile.c_str() );

		std::ifstream meshFileReadOnly;
		meshFileReadOnly.open(meshFile,std::ios::binary); 
			
		if (meshFileReadOnly.fail())
		{
			LogMessage( "Failed to open mesh file" );
			mesh=NULL;
		}
		else
		{
			meshFileReadOnly.read(reinterpret_cast<char*>(&meshCount), sizeof(int) );
			mesh= new cMesh[meshCount];

			//Creating and Initializing mesh
			for(int i=0; i<meshCount; ++i)
			{
				int vertexCount=0;
				int triangleCount=0;
				meshFileReadOnly.read(reinterpret_cast<char*>(&vertexCount), sizeof(int) );
				meshFileReadOnly.read(reinterpret_cast<char*>(&triangleCount), sizeof(int) );

				if(mesh[i].Initialize(m_direct3dDevice,m_direct3dInterface,meshFile,i_rotation,i_position, vertexCount, triangleCount) )
				{
						LogMessage( "Successful to Initialize buffer" );
				}		

				if(!mesh[i].createBuffers() )
				{
						LogMessage( "Failed to create buffer" );				
				}

				if(!mesh[i].fillBuffers(vertexCount, triangleCount, meshFileReadOnly) )
				{
							LogMessage( "Failed to fill buffer" );
												
				}
			}
						
			meshFileReadOnly.close();
		}
	
		std::ifstream textureFile;
		textureFile.open(i_textureFile); 

		if (textureFile.fail())
		{
			LogMessage( "Failed to open mesh file" );
		}
		else
		{
			for(int i=0; i<meshCount; ++i)
			{
				std::string textureName;
				textureFile>>textureName;
				if(textureName=="none")
					textureName=textureName+".png";

				textureName= "data/Textures/" +textureName;
				mesh[i].setTextureName(textureName);

				if(materialList.find( textureName ) == materialList.end())
				{
					material= new Material();
					material->Initialize(m_direct3dDevice,m_direct3dInterface);
					material->getMaterial(textureName);
					materialList.insert(std::pair<std::string,Material*>(textureName,material));
				}
			}		
			textureFile.close();
		}
	}

void Entity::getEntityFromEntity(Entity *inEntity, int id)
{
	std::map<std::string,Material*>::iterator it;
	
	std::string texture=mesh[id].getTextureName();
	it= materialList.find(texture);

	Material * newMaterial;
	if(it != materialList.end())
	{
		newMaterial= it->second;
	}
	cMesh* newMesh=&mesh[id];
	newMesh->LocalizeMesh();

	inEntity->meshCount=1;
	inEntity->setMesh(newMesh);
	inEntity->materialList.insert(std::pair<std::string,Material*>(mesh[id].getTextureName(),newMaterial));
}

void Entity::Update(Camera &i_camera, LightSource &i_light)
{
	std::map<std::string,Material*>::iterator it;

	for(int i=0; i<meshCount; ++i)
	{
		//std::string texture=mesh[i].getTextureName();
		//it= materialList.find(texture);

		//if(it != materialList.end())
	//	{
	//		it->second->Update(i_camera,mesh[i],i_light);
	//	}
		mesh[i].Update();
	}
	
	if(meshCount==1012)
	{
		for(int h=0; h< pathFindingLines.size(); ++h)
		{
			line_vertex line_vertices[2];

			line_vertices[0].x = pathFindingLines[h].vertex.x;
			line_vertices[0].y = pathFindingLines[h].vertex.y;
			line_vertices[0].z = pathFindingLines[h].vertex.z;
			line_vertices[0].color = pathFindingLines[h].color;
 

			line_vertices[1].x = pathFindingLines[++h].vertex.x;
			line_vertices[1].y = pathFindingLines[h].vertex.y;
			line_vertices[1].z = pathFindingLines[h].vertex.z;
			line_vertices[1].color =pathFindingLines[h].color;

			m_direct3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, line_vertices , sizeof(line_vertex));
		}

		if(Octree::showDebugLines)
		{
			for(int h=0; h< Octree::debugLines.size(); ++h)
			{
				line_vertex line_vertices[2];

				line_vertices[0].x = Octree::debugLines[h].vertex.x;
				line_vertices[0].y = Octree::debugLines[h].vertex.y;
				line_vertices[0].z = Octree::debugLines[h].vertex.z;
				line_vertices[0].color = Octree::debugLines[h].color;
 

				line_vertices[1].x = Octree::debugLines[++h].vertex.x;
				line_vertices[1].y = Octree::debugLines[h].vertex.y;
				line_vertices[1].z = Octree::debugLines[h].vertex.z;
				line_vertices[1].color = Octree::debugLines[h].color;

				m_direct3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, line_vertices , sizeof(line_vertex));
			}
		}	
	}
}


  cMesh *Entity::getMesh()
  {
	return mesh;
  }

  void Entity::setMesh(cMesh* i_mesh)
  {
	 mesh=i_mesh;
  }

  void Entity::setMaterial(Material* i_material)
  {
	 material=i_material;
  }

    Material *Entity::getMaterial()
  {
	return material;
  }

}

