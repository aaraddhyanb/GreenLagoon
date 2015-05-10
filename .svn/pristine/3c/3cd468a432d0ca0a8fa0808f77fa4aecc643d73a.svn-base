#ifndef ENTITY_H
#define ENTITY_H

#include"Material.h"
#include"cMesh.h"
#include<map>

namespace cs6963
{
	class Entity
	{
		private:
			cMesh *mesh;
			Material *material;
			
            int materialCount;
			char *meshFile;

			IDirect3D9* m_direct3dInterface;
		    IDirect3DDevice9* m_direct3dDevice;

		public:

			Entity(){}
			Entity(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface);

			void getEntity(const std::string &i_entity, const std::string &i_textureFile, D3DXVECTOR3 i_position, float i_rotation);
			void getEntityFromEntity(Entity *inEntity, int id);

			void Update(Camera &i_camera, LightSource &i_light);
			
			static std::vector<renderAsLines> pathFindingLines;

			void setMesh(cMesh *i_mesh);
			cMesh *getMesh();
			void setMaterial(Material *i_material);
			Material *getMaterial();

			std::map<std::string, Material*> materialList;
			int meshCount;
		};

}

#endif