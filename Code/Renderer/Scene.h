#ifndef SCENE_H
#define SCENE_H

#include"Entity.h"
#include <d3dx9math.h>
#include<vector>

namespace cs6963
{
	class Scene
	{
		private:

		    std::vector<class Entity *> entityList;

		    LightSource *light;

			D3DXVECTOR3 cameraPosition;
			D3DXVECTOR4 lightPosition;
			D3DXVECTOR4 lightColor;

			IDirect3D9* m_direct3dInterface;
		    IDirect3DDevice9* m_direct3dDevice;

		public:

			Scene();

			void Initialize(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface);
			
			Entity *Scene::AddEntity(std::string meshFile, std::string textureFile, float posX, float posY, float posZ, float rotation);
			Entity *Scene::AddEntityToScene(Entity *parentEntity, int id);

		    bool Update();
	
			void getScene();
			
			std::vector<class Entity *> getEntityList();

		    D3DXVECTOR4 getLightColor();

		    D3DXVECTOR4 getLightPosition();

		    D3DXVECTOR3 getCameraPosition();

		    int getEntityCount();

			Camera *camera;
 };

}

#endif