#include "Scene.h"
#include <math.h>
#include <queue>

#include "SpatialPartition.h"

#define EPSILON 0.02

namespace cs6963
{

	Scene::Scene()
	{
		camera=new Camera();
		light=new LightSource();
		entityList.clear();
	}

	void Scene::Initialize(IDirect3DDevice9 * i_direct3dDevice,IDirect3D9 * i_direct3dInterface)
	{
		 m_direct3dInterface=i_direct3dInterface;
	     m_direct3dDevice=i_direct3dDevice;
	}

	void Scene::getScene()
	{
		std::ifstream file;
	    file.open("data/graphicsConfig.txt"); 
			
	    if (file.fail())
	    {
			LogMessage( "Failed to open scene file" );  	
		}
		else
		{	
			LogMessage( "Successfully opened Scene file" );

			std::string word;
		
        	while(!file.eof())
		 	{
				file>>word;

				if(word=="cameraPosition")
				{
					file>>cameraPosition.x>>cameraPosition.y>>cameraPosition.z;
					camera->CreateCamera(cameraPosition);
					word="";
				}

				if(word=="lightPosition")
				{
					file>>lightPosition.x>>lightPosition.y>>lightPosition.z>>lightPosition.w;
					light->SetPosition(lightPosition);
					word="";
				}

				if(word=="lightColor")
				{
					file>>lightColor.x>>lightColor.y>>lightColor.z;
					word="";
				}

				if(word=="lightIntensity")
				{
					file>>lightColor.w;
					light->SetColor(lightColor);
					word="";
				}
		   }
		   file.close();
		   cMesh::createOctTree();
	}

}

Entity *Scene::AddEntity(std::string meshFile, std::string textureFile, float posX, float posY, float posZ, float rotation)
{
	D3DXVECTOR3 position= D3DXVECTOR3(posX,posY,posZ);
	Entity *entity=new Entity(m_direct3dDevice,m_direct3dInterface);
	entity->getEntity(meshFile,textureFile,position,rotation);
	entityList.push_back(entity);
	return entity;
}

Entity *Scene::AddEntityToScene(Entity *parentEntity, int id)
{
	Entity *entity=new Entity(m_direct3dDevice,m_direct3dInterface);
	parentEntity->getEntityFromEntity(entity, id);
	entityList.push_back(entity);
	return entity;
}

 bool Scene::Update()
 {
	 light->Update();
	 camera->Update();

	 m_direct3dDevice->BeginScene();
	 for(int i=0;i<entityList.size();i++)
	 {
		entityList[i]->Update(*camera,*light);		
	 }
	m_direct3dDevice->EndScene();
	return true;
 }


  std::vector<class Entity *> Scene::getEntityList()
  {
	return entityList;
  }

   D3DXVECTOR4 Scene::getLightColor()
   {
	   return lightColor;

   }

    D3DXVECTOR4 Scene::getLightPosition()
   {
	   return lightPosition;

   }

	 D3DXVECTOR3 Scene::getCameraPosition()
   {
	   return cameraPosition;

   }

 
}
