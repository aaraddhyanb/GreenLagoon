#include "stdafx.h"
#include "SpatialPartition.h"

#include <math.h>
#include <fstream>
#include <queue>
#include <map>

void cs6963::Octree::initialize(std::string i_fileName, int i_granularity)
{
	granularity=i_granularity;
	rootNode= nullptr;
	filename= i_fileName;
}

void cs6963::Octree::rayIntersectBB()
{

}

void maxValue(vector<cs6963::triangle> i_tri, float &i_maxX, float &i_maxY, float &i_maxZ )
{
	for(int i=0;i < i_tri.size(); ++i)
	{
		if( i_maxX < abs(i_tri[i].tri[0].pos[0]) )
		{
			i_maxX= abs(i_tri[i].tri[0].pos[0]);
		}
		if( i_maxX < abs(i_tri[i].tri[1].pos[0]) )
		{
			i_maxX= abs(i_tri[i].tri[1].pos[0]);
		}
		if( i_maxX < abs(i_tri[i].tri[2].pos[0]) )
		{
			i_maxX= abs(i_tri[i].tri[2].pos[0]);
		}


		if( i_maxY < abs(i_tri[i].tri[0].pos[1]) )
		{
			i_maxY= abs(i_tri[i].tri[0].pos[1]);
		}
		if( i_maxY < abs(i_tri[i].tri[1].pos[1]) )
		{
			i_maxY= abs(i_tri[i].tri[1].pos[1]);
		}
		if( i_maxY < abs(i_tri[i].tri[2].pos[1]) )
		{
			i_maxY= abs(i_tri[i].tri[2].pos[1]);
		}

		if( i_maxZ < abs(i_tri[i].tri[0].pos[2]) )
		{
			i_maxZ= abs(i_tri[i].tri[0].pos[2]);
		}
		if( i_maxZ < abs(i_tri[i].tri[1].pos[2]) )
		{
			i_maxZ= abs(i_tri[i].tri[1].pos[2]);
		}
		if( i_maxZ < abs(i_tri[i].tri[2].pos[2]) )
		{
			i_maxZ= abs(i_tri[i].tri[2].pos[2]);
		}
	}
}

/*

Dividing the box in 8 equal space for octree

               7      8
			/------------/
           / | 3    4  / |
         /---|-------/   |
		|    |     |     |
		|    |   5 |  6  |
		|  / ------|----/-
		| /        |  /
		------------/
		   1     2
*/
void formChildren(cs6963::OctNode * parent)
{
	if(parent->depth<=0)
		return;

	else if(parent!= NULL)
	{
		D3DXVECTOR3 center= D3DXVECTOR3( (parent->lfb.x+parent->rbt.x)/2,
			                             (parent->lfb.y+parent->rbt.y)/2,
										 (parent->lfb.z+parent->rbt.z)/2 );
		for(int i=0; i< 8; ++i)
		{
			cs6963::OctNode* node= new cs6963::OctNode;
		
			//1
			if(i==0)
			{
				node->lfb=parent->lfb;
				node->rbt=center;
			}
			//2
			if(i==1)
			{
				node->lfb= D3DXVECTOR3(center.x, parent->lfb.y, parent->lfb.z);
				node->rbt= D3DXVECTOR3(parent->rbt.x, center.y, center.z);
			}
			//3
			if(i==2)
			{
				node->lfb= D3DXVECTOR3(parent->lfb.x, center.y, parent->lfb.z);
				node->rbt= D3DXVECTOR3(center.x, parent->rbt.y, center.z);
			}
			//4
			if(i==3)
			{
				node->lfb= D3DXVECTOR3(center.x, center.y, parent->lfb.z);
				node->rbt= D3DXVECTOR3(parent->rbt.x, parent->rbt.y, center.z);
			}
			//5
			if(i==4)
			{
				node->lfb= D3DXVECTOR3(parent->lfb.x, parent->lfb.y, center.z);
				node->rbt= D3DXVECTOR3(center.x, center.y, parent->rbt.z);
			}
			//6
			if(i==5)
			{
				node->lfb= D3DXVECTOR3(center.x, parent->lfb.y, center.z);
				node->rbt= D3DXVECTOR3(parent->rbt.x, center.y, parent->rbt.z);
			}
			//7
			if(i==6)
			{
				node->lfb= D3DXVECTOR3(parent->lfb.x, center.y, center.z);
				node->rbt= D3DXVECTOR3(center.x, parent->rbt.y, parent->rbt.z);
			}
			//8
			if(i==7)
			{
				node->lfb= center;
				node->rbt= parent->rbt;
			}

			//Bump it up or Drop it down
			for(std::vector<cs6963::triangle>::iterator it=parent->triangleList.begin(); it!=parent->triangleList.end();)
			{
				bool triangleFound=false;
				if( (node->lfb.x<= it->tri[0].pos[0] && node->rbt.x>= it->tri[0].pos[0]) &&
					(node->lfb.y<= it->tri[0].pos[1] && node->rbt.y>= it->tri[0].pos[1]) &&
					(node->lfb.z<= it->tri[0].pos[2] && node->rbt.z>= it->tri[0].pos[2])  )
				{
					if( (node->lfb.x<= it->tri[1].pos[0] && node->rbt.x>= it->tri[1].pos[0]) &&
						(node->lfb.y<= it->tri[1].pos[1] && node->rbt.y>= it->tri[1].pos[1]) &&
						(node->lfb.z<= it->tri[1].pos[2] && node->rbt.z>= it->tri[1].pos[2])  )
					{
						if( (node->lfb.x<= it->tri[2].pos[0] && node->rbt.x>= it->tri[2].pos[0]) &&
							(node->lfb.y<= it->tri[2].pos[1] && node->rbt.y>= it->tri[2].pos[1]) &&
							(node->lfb.z<= it->tri[2].pos[2] && node->rbt.z>= it->tri[2].pos[2])  )
						{
							node->triangleList.push_back((*it));
							it= parent->triangleList.erase(it);
							triangleFound=true;
						}
					}
				}
				if(!triangleFound)
					++it;
			}

			//if no triangles then set to null
			if(node->triangleList.size()<=0)
			{
				delete node;
				parent->child[i] = nullptr;
			}else
			{
				parent->child[i] = node;
				node->depth=parent->depth -1;
				formChildren(node);
			}
		}
	}
}


void cs6963::Octree::createOctTree()
{
	vector< vertex> vertices;
	vector< int> indices;
	vector< triangle> triangles;

	std::string collisionMeshLink= filename;
	std::string txt(".txt");
	collisionMeshLink=collisionMeshLink+ txt;
		
	std::ifstream file;
	file.open(collisionMeshLink); 

	if (file.fail())
	{
	  printf("Failed to open collision file" );
	}
	else
	{
		std::string vert;
		std::string ind;
		int numberOfVertices;
		int numberOfIndices;

		file>>vert;
		file>>numberOfVertices;
		file>>ind;
		file>>numberOfIndices;
		file>>vert;

		for(int m=0; m< numberOfVertices; ++m)
		{
			vertex v;
			file>>v.pos[0];
            file>>v.pos[1];
			file>>v.pos[2];
			
			vertices.push_back(v);
		}
		file>>ind;
        for(int m=0; m< numberOfIndices; ++m)
		{
			int index;
			file>>index;
			indices.push_back(index);
		}
	    file.close();
	}
	//form triangles
	for(int m=0; m< indices.size(); ++m)
	{
		triangle atri;
		atri.tri[0]=vertices[indices[m]];
		atri.tri[1]=vertices[indices[++m]];
		atri.tri[2]=vertices[indices[++m]];

        triangles.push_back(atri);
	}

	//find bounds
	float maxX =0.f;
	float maxY =0.f;
	float maxZ =0.f;

	maxValue(triangles, maxX, maxY, maxZ);

	rootNode= new OctNode;
	rootNode->lfb=D3DXVECTOR3(-maxX, -maxY, -maxZ);
	rootNode->rbt=D3DXVECTOR3(maxX, maxY, maxZ);
	rootNode->triangleList=triangles;
	 
	for(int j=0; j< 8; ++j)
	{
		rootNode->child[j]=nullptr;
	}

	rootNode->depth=granularity;

	formChildren(rootNode);
}


void cs6963::Octree::writeToFile(std::string OctreeFile)
{
	//tranverse and print octree
	std::vector<OctNode *> stack;
	stack.push_back(rootNode);
	int numberOfTriangles=0;
#if 0
	//-Write to file--Txt
	FILE *fileptr=nullptr;
	OctreeFile.append(".txt");
	fileptr= fopen(OctreeFile.c_str(),"w");
	if(fileptr==nullptr)
	{
		printf("Failed to open file");
	}
	while(stack.size())
	{
		OctNode * currentNode= stack.back();
		stack.pop_back();

		if(currentNode==nullptr)
		{
			fprintf(fileptr, "node -1\n" );
		}
		else
		{
			fprintf(fileptr, "node %d\n", currentNode->depth );
			fprintf(fileptr, "TotalTriangles %d\n", currentNode->triangleList.size());
			numberOfTriangles+=currentNode->triangleList.size();

			for(int x=0;x <currentNode->triangleList.size(); ++x)
			{
				fprintf(fileptr, "%f %f %f\n", currentNode->triangleList[x].tri[0].pos[0], currentNode->triangleList[x].tri[0].pos[1], currentNode->triangleList[x].tri[0].pos[2]);
				fprintf(fileptr, "%f %f %f\n", currentNode->triangleList[x].tri[1].pos[0], currentNode->triangleList[x].tri[1].pos[1], currentNode->triangleList[x].tri[1].pos[2]);
				fprintf(fileptr, "%f %f %f\n", currentNode->triangleList[x].tri[2].pos[0], currentNode->triangleList[x].tri[2].pos[1], currentNode->triangleList[x].tri[2].pos[2]);
			}
			for(int x=7; x >=0; --x)
			{
				stack.push_back(currentNode->child[x]);																																																																																
			}
		}
	}
	fprintf(fileptr, "\n\n\nTriangles %d", numberOfTriangles);
    fclose(fileptr);
#endif

	//Fill the binary file
	OctreeFile.append(".bin");
	std::ofstream outfile(OctreeFile,std::ios::binary);
	while(stack.size())
	{
		OctNode * currentNode= stack.back();
		stack.pop_back();

		if(currentNode==nullptr)
		{
			int minusOne=-1;
			outfile.write(reinterpret_cast<const char*>(&minusOne), sizeof(int));
		}
		else
		{
			outfile.write(reinterpret_cast<const char*>(&(currentNode->depth)), sizeof(int));
			outfile.write(reinterpret_cast<const char*>(&(currentNode->lfb.x)), sizeof(float));
			outfile.write(reinterpret_cast<const char*>(&(currentNode->lfb.y)), sizeof(float));
            outfile.write(reinterpret_cast<const char*>(&(currentNode->lfb.z)), sizeof(float));

			outfile.write(reinterpret_cast<const char*>(&(currentNode->rbt.x)), sizeof(float));
			outfile.write(reinterpret_cast<const char*>(&(currentNode->rbt.y)), sizeof(float));
            outfile.write(reinterpret_cast<const char*>(&(currentNode->rbt.z)), sizeof(float));

			int numberOfTriangles= currentNode->triangleList.size();
			outfile.write(reinterpret_cast<const char*>(&(numberOfTriangles)), sizeof(int));

			for(int x=0;x <currentNode->triangleList.size(); ++x)
			{
				for(int y=0; y< 3; ++y)
				{
				    outfile.write(reinterpret_cast<const char*>(&(currentNode->triangleList[x].tri[y].pos[0])), sizeof(float));
					outfile.write(reinterpret_cast<const char*>(&(currentNode->triangleList[x].tri[y].pos[1])), sizeof(float));
					outfile.write(reinterpret_cast<const char*>(&(currentNode->triangleList[x].tri[y].pos[2])), sizeof(float));
				}
			}
			for(int x=7; x >=0; --x)
			{
				stack.push_back(currentNode->child[x]);																																																																																
			}
		}
	}
	outfile.close();
	
}


cs6963::Octree* cs6963::Octree::readFromFile(std::string OctreeFile)
{
	//Fill the binary file
	OctreeFile.append(".bin");
	std::ifstream infile;
	infile.open(OctreeFile,std::ios::binary);
	
	if (infile.fail())
		printf( "Failed to open octree file" );
	
	Octree *octree=this;
	int getnum=0;
	std::vector<NodeValuePair > stack;

	NodeValuePair OctMap;
	OctMap.nodeAddress=nullptr;
	OctMap.value=-1;

	stack.push_back(OctMap);

	while(stack.size())
	{
		OctNode *parentNode=stack.back().nodeAddress;
		int childAt= stack.back().value;
		OctNode *newNode= nullptr;

		int depth=0;
		infile.read(reinterpret_cast<char*>(&depth), sizeof(int) );
		if(depth>0)
		{
			newNode= new OctNode;
			newNode->depth=depth;

			//node exist; min max
			infile.read(reinterpret_cast<char*>(&(newNode->lfb.x)), sizeof(float) );
			infile.read(reinterpret_cast<char*>(&(newNode->lfb.y)), sizeof(float) );
			infile.read(reinterpret_cast<char*>(&(newNode->lfb.z)), sizeof(float) );

			infile.read(reinterpret_cast<char*>(&(newNode->rbt.x)), sizeof(float) );
			infile.read(reinterpret_cast<char*>(&(newNode->rbt.y)), sizeof(float) );
			infile.read(reinterpret_cast<char*>(&(newNode->rbt.z)), sizeof(float) );

			//node exist; read triangles
			int numOfTriangles;
			infile.read(reinterpret_cast<char*>(&numOfTriangles), sizeof(int) );
			getnum+=numOfTriangles;

			triangle newTriangle;
			for(int d=0; d< numOfTriangles; ++d)
			{
				for(int y=0; y< 3; ++y)
				{
				    infile.read(reinterpret_cast<char*>(&(newTriangle.tri[y].pos[0])), sizeof(float));
					infile.read(reinterpret_cast<char*>(&(newTriangle.tri[y].pos[1])), sizeof(float));
					infile.read(reinterpret_cast<char*>(&(newTriangle.tri[y].pos[2])), sizeof(float));
				}
				newNode->triangleList.push_back(newTriangle);
			}

			if(childAt==-1)
			{
				stack.back().nodeAddress=newNode;
				octree->rootNode=stack.back().nodeAddress;
			    stack.back().value=stack.back().value+1;
			}
			else
			{
				stack.back().nodeAddress->child[childAt]=newNode;
				stack.back().value=stack.back().value+1;
				
				if(stack.back().value==8)
					stack.pop_back();

				//push this new node
				NodeValuePair newOctMap;
				newOctMap.nodeAddress=newNode;
				newOctMap.value=0;
				stack.push_back(newOctMap);
			}
		}
		else
		{
			//node doesn't exist; read nothings
			stack.back().nodeAddress->child[childAt]=newNode;
		    stack.back().value=stack.back().value+1;
		}

		//all nodes achieved
		if(stack.back().value==8)
			stack.pop_back();

	}
	return octree;
}