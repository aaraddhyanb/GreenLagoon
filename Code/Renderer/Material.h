#ifndef MATERIAL_H
#define MATERIAL_H

#include"Effect.h"

namespace cs6963
{
	class Material
	{
		private:

			Effect *effect;
			
			char *textureFile;

			char* effectName;

			float alpha;

			LPDIRECT3DTEXTURE9 normalMap;

			IDirect3D9* m_direct3dInterface;
		    IDirect3DDevice9* m_direct3dDevice;

		public:


			LPDIRECT3DTEXTURE9 pTexture;

			Material(){}

			void Initialize(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface);

			Material(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface);
		  
			void getMaterial(std::string i_texture);

			void Update(Camera &i_camera, cMesh &i_mesh, LightSource &i_light);
			
			Effect * getEffect();

			char*  getTextureFile();

			float getAlphaValue();
		};

}

#endif