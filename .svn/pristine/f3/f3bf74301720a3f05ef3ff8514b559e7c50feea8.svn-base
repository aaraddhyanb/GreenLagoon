#ifndef EFFECT_H
#define EFFECT_H

#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include<iostream>
#include<cstdint>
#include <d3d9.h>
#include <D3DX9Shader.h>
#include"Logging.h"
#include "cTime.h"
#include "Camera.h"
#include "LightSource.h"
#include "cMesh.h"



namespace cs6963
{
	class Effect
	{
		private:
			struct
			{
				IDirect3DVertexShader9* vertexShader;
				ID3DXConstantTable* vertexShaderConstantTable;
				IDirect3DPixelShader9* fragmentShader;
				ID3DXConstantTable* fragmentShaderConstantTable;
			} m_scene;
	
		 	IDirect3D9* m_direct3dInterface;
		    IDirect3DDevice9* m_direct3dDevice;

			char *vertexShaderFile;
			
			char *fragmentShaderFile;

			char *blending;


		public:

			Effect(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface);
			void getEffect();
		
			void Update(Camera &i_camera, cMesh &i_mesh, LightSource &i_light, float i_alpha,LPDIRECT3DTEXTURE9 i_texture,LPDIRECT3DTEXTURE9 i_normalMap) const;
			bool Initialize();
		
			bool Release();
			bool Shutdown();

			bool createVertexShader();
			bool createFragmentShader();

			char * getVertexShader();
			char * getFragmentShader();
			char *getBlending();	
	};
}

#endif