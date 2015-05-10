#ifndef _FBXMAIN_
#define _FBXMAIN_

#include "stdio.h"
#include "conio.h"

#include <fbxsdk.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

struct MyVertex
{
   float pos[3];
   float Uvs[2];
};

struct Mesh
{
	std::map <int,MyVertex> IndexVertexPair;
	std::vector<int> IndexData;
};

std::map<std::string,Mesh> MeshData;

FbxManager* g_pFbxSdkManager = nullptr;
FbxVector4* pVertices; 
FILE *fileptr=nullptr;
std::string meshName="mesh";

void traverseNode(FbxNode* node);

void LoadFBX()
{
   if(g_pFbxSdkManager == nullptr)
   {
      g_pFbxSdkManager = FbxManager::Create();

      FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT );
      g_pFbxSdkManager->SetIOSettings(pIOsettings);
   }

   FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager,"");
   FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager,"");

   bool bSuccess = pImporter->Initialize("CollisionOnly.fbx", -1, g_pFbxSdkManager->GetIOSettings() );
   if(!bSuccess) 
   {
	   printf("cannot open");
   }

   bSuccess = pImporter->Import(pFbxScene);
   if(!bSuccess) 
   {
	   printf("cannot import");
   }

   pImporter->Destroy();

   FbxNode* pFbxRootNode = pFbxScene->GetRootNode();
   traverseNode(pFbxRootNode);

   //--------------------------------------------------------------------------
   //Writing to file
   std::map<std::string,Mesh>::iterator it;
   int count;
   for(count=0,it=MeshData.begin(); it!=MeshData.end(); ++it,++count)
   {
	   std::stringstream meshNumber;
	   meshNumber<<count+1;
	   std::string index=meshNumber.str();

	   std::string newTexture=meshName;
	   newTexture.append(index).append("Texture").append(".txt");
	   fileptr= fopen(newTexture.c_str(),"w");
	   fprintf(fileptr, "%s", it->first.c_str());
	   fclose(fileptr);


	   std::string newMeshName=meshName;
	   newMeshName.append(index).append(".txt");
	   fileptr= fopen(newMeshName.c_str(),"w");
		if(fileptr==nullptr)
		{
			printf("Failed to open file");
		}
		
	   //---------------------------------------------------------------------------
		fprintf(fileptr, "TotalVertices %d\n", it->second.IndexVertexPair.size());
		fprintf(fileptr, "TotalIndices %d\n", it->second.IndexData.size());

	   fprintf(fileptr, "Vertices\n");
	   for(int i=0; i<it->second.IndexVertexPair.size(); ++i)
	   {
		   fprintf(fileptr, "%f", it->second.IndexVertexPair.find(i)->second.pos[0]);
					   fprintf(fileptr, "     %f", it->second.IndexVertexPair.find(i)->second.pos[1]);
					   fprintf(fileptr, "     %f\n", it->second.IndexVertexPair.find(i)->second.pos[2]);
	   }
	   //---------------------------------------------------------------------------
	   fprintf(fileptr, "Normals\n");
	   for(int i=0; i<it->second.IndexVertexPair.size(); ++i)
	   {
		 fprintf(fileptr, "%f",it->second.IndexVertexPair.find(i)->second.pos[0]);
					   fprintf(fileptr, "     %f", it->second.IndexVertexPair.find(i)->second.pos[1]);
					   fprintf(fileptr, "     %f\n", it->second.IndexVertexPair.find(i)->second.pos[2]);
	   }
	   //---------------------------------------------------------------------------
		  fprintf(fileptr, "Colors\n");
	   for(int i=0; i<it->second.IndexVertexPair.size(); ++i)
	   {
		 fprintf(fileptr, "255");
					   fprintf(fileptr, "     255");
					   fprintf(fileptr, "     255\n");
	   }
	   //---------------------------------------------------------------------------
		 fprintf(fileptr, "UV\n");
	   for(int i=0; i<it->second.IndexVertexPair.size(); ++i)
	   {
		 fprintf(fileptr, "%f",it->second.IndexVertexPair.find(i)->second.Uvs[0]);
					   fprintf(fileptr,"       %f\n",it->second.IndexVertexPair.find(i)->second.Uvs[1]);
	   }
	   //---------------------------------------------------------------------------
		fprintf(fileptr, "Indices\n");
	   for(int i=0; i<it->second.IndexData.size(); ++i)
	   {
		   fprintf(fileptr, "%d   ", it->second.IndexData[i]);	
		   if( (i+1)%3==0)
			   fprintf(fileptr,"\n");
	   }
	   //---------------------------------------------------------------------------
	   fclose(fileptr);
   }
  
}

void traverseNode(FbxNode* node)
{
   if(node)
   {
	   if(!node->GetChildCount())
		  return;

	  std::string textureName;
	  //------------------------------------------------------------------------------
	  //texture Name of mesh
      for(int i = 0; i < node->GetChildCount(); i++)
      {
         FbxNode* pFbxChildNode = node->GetChild(i);

         if(pFbxChildNode->GetNodeAttribute() == NULL)
			 return;

         FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

         if(AttributeType == FbxNodeAttribute::eMesh)
		 {
			 for( int l = 0; l < pFbxChildNode->GetSrcObjectCount<FbxSurfaceMaterial>(); ++l )
			 {
				FbxSurfaceMaterial *material = pFbxChildNode->GetSrcObject<FbxSurfaceMaterial>(l);

				for( int j = 0; j < FbxLayerElement::sTypeTextureCount; ++j )
				{
						FbxProperty textureProperty = material->FindProperty(  FbxLayerElement::sTextureChannelNames[j] );
						if( textureProperty.IsValid() )
						{
						  for( int k = 0; k < textureProperty.GetSrcObjectCount<FbxTexture>(); ++k )
						  {
							{
								FbxTexture *texture = textureProperty.GetSrcObject<FbxTexture>( k );
								if( texture )
								{
									if( strcmp(textureProperty.GetName(), "DiffuseColor") != 0 )
										continue;
									FbxFileTexture *fileTexture = FbxCast<FbxFileTexture>( texture );
									textureName = fileTexture->GetFileName();
								}
							}
						}
					}
				}
			}
		    //-------------------------------------------------------------------------------------------
		    std::map<std::string,Mesh>::iterator it; 
		    it=MeshData.find(textureName);

			if(it!=MeshData.end() )
			{
				 FbxMesh* pMesh = (FbxMesh*) pFbxChildNode->GetNodeAttribute();
				 // FbxGeometryConverter *triangulator= new FbxGeometryConverter(g_pFbxSdkManager);
				 //  pMesh= triangulator->TriangulateMesh(pMesh);

				 pVertices = pMesh->GetControlPoints();
				 Mesh newTempMesh;

				 for (int j = 0; j < pMesh->GetPolygonCount(); j++)
				 {
					int iNumVertices = pMesh->GetPolygonSize(j);
					assert( iNumVertices == 3 );

					for (int k = 0; k < iNumVertices; ++k)
					{
					   int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

					   	MyVertex vertex;
						vertex.pos[0] = (float)pVertices[iControlPointIndex].mData[0];
						vertex.pos[1] = (float)pVertices[iControlPointIndex].mData[1];
						vertex.pos[2] = (float)pVertices[iControlPointIndex].mData[2];
						
						FbxStringList uvNames;
						pMesh->GetUVSetNames(uvNames);
						FbxVector2 texCoord;
						bool mapUV=false;

						pMesh->GetPolygonVertexUV(j, k, uvNames[0], texCoord, mapUV);
						vertex.Uvs[0] = (float)texCoord.mData[0];
						vertex.Uvs[1] = (float)texCoord.mData[1];

						if(find(newTempMesh.IndexData.begin(), newTempMesh.IndexData.end(), iControlPointIndex) != newTempMesh.IndexData.end() )
						{
							newTempMesh.IndexData.push_back(iControlPointIndex);
						}
						else
						{
							newTempMesh.IndexVertexPair.insert( std::pair<int,MyVertex>(iControlPointIndex,vertex));

						    newTempMesh.IndexData.push_back(iControlPointIndex);
						}
					}  //k
				 }   //j
				 int numberOfVerts=it->second.IndexVertexPair.size();
				 for(int j=0; j<newTempMesh.IndexData.size(); ++j)
				 {
					int newIndex = numberOfVerts + newTempMesh.IndexData[j];
					it->second.IndexData.push_back(newIndex);
				 }
				 for(int j=0; j<newTempMesh.IndexVertexPair.size(); ++j)
				  {
					  int newIndex = numberOfVerts + newTempMesh.IndexVertexPair.find(j)->first;
					  MyVertex newVertex;
					  newVertex.pos[0] = newTempMesh.IndexVertexPair[j].pos[0];
					  newVertex.pos[1] = newTempMesh.IndexVertexPair[j].pos[1];
					  newVertex.pos[2] = newTempMesh.IndexVertexPair[j].pos[2];

					  newVertex.Uvs[0] = newTempMesh.IndexVertexPair[j].Uvs[0];
					  newVertex.Uvs[1] = newTempMesh.IndexVertexPair[j].Uvs[1];

					  it->second.IndexVertexPair.insert( std::pair<int,MyVertex>(newIndex,newVertex));
				  }
		     }
			else
			{
				Mesh newMesh;
				MeshData.insert(std::pair<std::string,Mesh>(textureName,newMesh));
				it=MeshData.find(textureName);

				FbxMesh* pMesh = (FbxMesh*) pFbxChildNode->GetNodeAttribute();
				pVertices = pMesh->GetControlPoints();

				for (int j = 0; j < pMesh->GetPolygonCount(); j++)
				 {
					int iNumVertices = pMesh->GetPolygonSize(j);
					assert( iNumVertices == 3 );

					for (int k = 0; k < iNumVertices; ++k)
					{
					   int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

					    MyVertex vertex;
						vertex.pos[0] = (float)pVertices[iControlPointIndex].mData[0];
						vertex.pos[1] = (float)pVertices[iControlPointIndex].mData[1];
						vertex.pos[2] = (float)pVertices[iControlPointIndex].mData[2];
					
						FbxStringList uvNames;
						pMesh->GetUVSetNames(uvNames);
						FbxVector2 texCoord;
						bool mapUV=false;

						pMesh->GetPolygonVertexUV(j, k, uvNames[0], texCoord, mapUV);
						vertex.Uvs[0] = (float)texCoord.mData[0];
						vertex.Uvs[1] = (float)texCoord.mData[1];

					   if(find(it->second.IndexData.begin(), it->second.IndexData.end(), iControlPointIndex) != it->second.IndexData.end() )
						{
							it->second.IndexData.push_back(iControlPointIndex);
						}
						else
						{
							it->second.IndexVertexPair.insert( std::pair<int,MyVertex>(iControlPointIndex,vertex));

						    it->second.IndexData.push_back(iControlPointIndex);
						}
					}  //k
				 }   //j

			}
		}

		traverseNode(pFbxChildNode);
     }
   }
}
  
#endif //_FBXMAIN_