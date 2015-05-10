#include"Material.h"


namespace cs6963
{
	Material::Material(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface)
	{
		m_direct3dDevice=i_direct3dDevice;
		m_direct3dInterface=i_direct3dInterface;       
	}

	void Material::Initialize(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface)
	{
		m_direct3dDevice=i_direct3dDevice;
		m_direct3dInterface=i_direct3dInterface;       
	}

	void Material::getMaterial(std::string i_texture)
	{
		effect = new Effect(m_direct3dDevice,m_direct3dInterface);
		effect->getEffect();

		//overridding texture
		std::string tempTextureFile=  i_texture;

		textureFile = (char*)malloc( sizeof( char ) *(tempTextureFile.length() +1) );
		strcpy( textureFile, tempTextureFile.c_str() );

		if(FAILED(D3DXCreateTextureFromFile(m_direct3dDevice,TEXT(textureFile),&pTexture) ) )
		{
			LogMessage( "Failed to load texture file" );
		}
		else
		{
			LogMessage( "Loaded texture successfully" );
		}

		std::string tempNormalMap="data/Textures/normalMap.png";
						
		char *normalM = (char*)malloc( sizeof( char ) *(tempNormalMap.length() +1) );
		strcpy( normalM, tempNormalMap.c_str() );

		if(FAILED(D3DXCreateTextureFromFile(m_direct3dDevice,TEXT(normalM),&normalMap) ) )
		{
			LogMessage( "Failed to load texture file" );
		}
		else
		{
			LogMessage( "Loaded texture successfully" );
		}			  
		alpha=1.0f;
	}

	void Material::Update(Camera &i_camera, cMesh &i_mesh, LightSource &i_light)
	{
		effect->Update(i_camera,i_mesh,i_light,alpha,pTexture,normalMap);
	}

		
  char *Material::getTextureFile()
  {
	return textureFile;
  }

  Effect *Material::getEffect()
  {
	return effect;
  }

 float Material::getAlphaValue()
 {
	 return alpha;
 }

}

