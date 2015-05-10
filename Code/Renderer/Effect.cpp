#include"Effect.h"

namespace cs6963
{
	Effect::Effect(IDirect3DDevice9 * i_direct3dDevice,IDirect3D9 * i_direct3dInterface)
	{
	    m_direct3dInterface=i_direct3dInterface;
	     m_direct3dDevice=i_direct3dDevice;
		 m_scene.vertexShader = NULL;
		 m_scene.vertexShaderConstantTable = NULL;
		 m_scene.fragmentShader = NULL;
		 m_scene.fragmentShaderConstantTable = NULL;
	}

	void Effect:: getEffect()
	{
		std::string tempVertexShaderFile="data/VertexShaders/example.vp";
		std::string tempFragmentShaderFile="data/FragmentShaders/example.fp";
		std::string tempblend="None";
		
		vertexShaderFile = (char*)malloc( sizeof( char ) *(tempVertexShaderFile.length() +1) );
		strcpy( vertexShaderFile, tempVertexShaderFile.c_str() );
		if(!createVertexShader() )
		{
			LogMessage( "Failed to create vertex shader file" );	
		}
    
		fragmentShaderFile = (char*)malloc( sizeof( char ) *(tempFragmentShaderFile.length() +1) );
		strcpy( fragmentShaderFile, tempFragmentShaderFile.c_str() );
		if(!createFragmentShader() )
		{
			LogMessage( "Failed to create fragment shader file" );
									
		}
     
		blending = (char*)malloc( sizeof( char ) *(tempblend.length() +1) );
		strcpy( blending, tempblend.c_str() );
	}


void Effect::Update(Camera &i_camera, cMesh &i_mesh, LightSource &i_light, float i_alpha,LPDIRECT3DTEXTURE9 i_texture,LPDIRECT3DTEXTURE9 i_normalMap) const
{
		m_direct3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	 // Set the shader programs
	 {
		HRESULT result = m_direct3dDevice->SetVertexShader( m_scene.vertexShader );
		assert( SUCCEEDED( result ) );
		result = m_direct3dDevice->SetPixelShader( m_scene.fragmentShader );
		assert( SUCCEEDED( result ) );

		// Set the elapsed time into the shaders' uniform variables
		// (we will discuss this more in later classes)
		{
			float secondsElapsed = g_time.GetTotalSecondsElapsed();
			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "g_secondsElapsed";
					variable = m_scene.vertexShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					result = m_scene.vertexShaderConstantTable->SetFloat( m_direct3dDevice, variable, secondsElapsed );
					assert( SUCCEEDED( result ) );
				}
				else
				{
					// If the variable isn't used by the shader it won't be included in the compiled version;
					// this can make it hard to know whether to know a NULL handle is an error or not.
					// It is up to you how to handle this
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "g_worldMat";
					variable = m_scene.vertexShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{			
					D3DXMATRIX RotationY;
					
					D3DXMatrixRotationY( & RotationY, i_mesh.GetRotation() );

					D3DXMATRIX translation;
					D3DXMatrixTranslation( & translation, i_mesh.GetPosition().x, i_mesh.GetPosition().y, i_mesh.GetPosition().z );
					
				    D3DXMatrixMultiply(&RotationY, &RotationY, &translation);

					result = m_scene.vertexShaderConstantTable->SetMatrix( m_direct3dDevice, variable, & RotationY );
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "Model to World failed" );
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "g_viewMat";
					variable = m_scene.vertexShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					D3DXMATRIX transform_worldToView;

					transform_worldToView = i_camera.GetWorldToViewTransform();

					result = m_scene.vertexShaderConstantTable->SetMatrix( m_direct3dDevice, variable, & transform_worldToView );
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "World to View failed" );
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "g_projMat";
					variable = m_scene.vertexShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					D3DXMATRIX transform_viewToProjected;
					D3DXMatrixPerspectiveFovLH( & transform_viewToProjected, D3DX_PI / 4, 1.333f, 0.1f, 10000.0f );

					result = m_scene.vertexShaderConstantTable->SetMatrix( m_direct3dDevice, variable, & transform_viewToProjected );
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "View To Projection failed" );
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "g_secondsElapsed";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					result = m_scene.fragmentShaderConstantTable->SetFloat( m_direct3dDevice, variable, secondsElapsed );
					assert( SUCCEEDED( result ) );
				}
				else
				{
					// If the variable isn't used by the shader it won't be included in the compiled version;
					// this can make it hard to know whether to know a NULL handle is an error or not.
					// It is up to you how to handle this
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "normalTex";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					unsigned int index = m_scene.fragmentShaderConstantTable->GetSamplerIndex( variable );
				
					result = m_direct3dDevice->SetTexture(static_cast<DWORD>(index), i_normalMap);
					assert( SUCCEEDED( result ) );
		    	}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "tex";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					unsigned int index = m_scene.fragmentShaderConstantTable->GetSamplerIndex( variable );
				
					result = m_direct3dDevice->SetTexture(static_cast<DWORD>(index), i_texture);
					assert( SUCCEEDED( result ) );
		    	}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "i_lightSource";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					D3DXVECTOR4 lightPos=i_light.getLightPosition();
					result = m_scene.vertexShaderConstantTable->SetVector( m_direct3dDevice,variable,&lightPos);
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "Failed to load the value of light position" );
				}
			}

			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "lightParameter";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					D3DXVECTOR4 lightColor=i_light.getColor();
					result = m_scene.vertexShaderConstantTable->SetVector( m_direct3dDevice,variable,&lightColor);
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "Failed to load the value of light color" );
				}

			}
			{
				D3DXHANDLE variable;
				{
					D3DXHANDLE topLevelVariable = NULL;
					const char* variableName = "alpha";
					variable = m_scene.fragmentShaderConstantTable->GetConstantByName( topLevelVariable, variableName );
				}
				if ( variable != NULL )
				{
					result = m_scene.vertexShaderConstantTable->SetFloat( m_direct3dDevice,variable,i_alpha);
					assert( SUCCEEDED( result ) );
				}
				else
				{
					LogMessage( "Failed to load the value of light position" );
				}

			}
		}
	}
}


    // Create the vertex shader
    bool Effect::createVertexShader()
	{
		
		// Load the compiled vertex shader from disk
		void* compiledVertexShader;
		{   
		
			// Open the file
			const char* fileName =vertexShaderFile;
			HANDLE fileHandle;
			{
				DWORD desiredAccess = GENERIC_READ;
				DWORD otherProgramsCanStillReadTheFile = FILE_SHARE_READ;
				SECURITY_ATTRIBUTES* useDefaultSecurity = NULL;
				DWORD onlySucceedIfFileExists = OPEN_EXISTING;
				DWORD useDefaultAttributes = FILE_ATTRIBUTE_NORMAL;
				HANDLE dontUseTemplateFile = NULL;
				fileHandle = CreateFile( fileName, desiredAccess, otherProgramsCanStillReadTheFile,
					useDefaultSecurity, onlySucceedIfFileExists, useDefaultAttributes, dontUseTemplateFile );
				if ( fileHandle == INVALID_HANDLE_VALUE )
				{
					LogMessage( std::string( "Failed to open vertex shader " ) + fileName );
					return false;
				}
			}
			// Get the file's size
			DWORD fileSize;
			{
				LARGE_INTEGER fileSize_integer;
				if ( GetFileSizeEx( fileHandle, &fileSize_integer ) == TRUE )
				{
					// This is unsafe, because the file's size could be bigger than a DWORD
					fileSize = static_cast<DWORD>( fileSize_integer.QuadPart );
				}
				else
				{
					LogMessage( std::string( "Couldn't get the size of vertex shader " ) + fileName );
					CloseHandle( fileHandle );
					return false;
				}
			}
			// Read the file's contents into temporary memory
			compiledVertexShader = malloc( fileSize );
			{
				DWORD bytesReadCount;
				OVERLAPPED* readSynchronously = NULL;
				if ( ReadFile( fileHandle, compiledVertexShader, fileSize,
					&bytesReadCount, readSynchronously ) == TRUE )
				{
					CloseHandle( fileHandle );
				}
				else
				{
					LogMessage( std::string( "Couldn't read the contents of vertex shader " ) + fileName );
					free( compiledVertexShader );
					CloseHandle( fileHandle );
					return false;
				}
			}
		}
		// Create the vertex shader object
		{
			HRESULT result = m_direct3dDevice->CreateVertexShader( reinterpret_cast<DWORD*>( compiledVertexShader ), &m_scene.vertexShader );
			if ( SUCCEEDED( result ) )
			{
				// Get the constant table from the vertex shader
				result = D3DXGetShaderConstantTable( reinterpret_cast<DWORD*>( compiledVertexShader ), &m_scene.vertexShaderConstantTable );
				if ( SUCCEEDED( result ) )
				{
					// Set the default values
					result = m_scene.vertexShaderConstantTable->SetDefaults( m_direct3dDevice );
					if ( FAILED( result ) )
					{
						LogMessage( "Couldn't set the vertex shader constant defaults" );
					}
				}
				free( compiledVertexShader );
				if ( FAILED( result ) )
				{
					LogMessage( "Couldn't get the vertex shader constant table" );
					return false;
				}
			}
			else
			{
				LogMessage( "Couldn't create the vertex shader object" );
				free( compiledVertexShader );
				return false;
			}
		}
     return true;
}

// Create the fragment shader object
bool Effect::createFragmentShader()
{

		// Load the compiled fragment shader from disk
		void* compiledFragmentShader;
		{

			// Open the file
			const char* fileName =fragmentShaderFile;
			HANDLE fileHandle;
			{
				DWORD desiredAccess = GENERIC_READ;
				DWORD otherProgramsCanStillReadTheFile = FILE_SHARE_READ;
				SECURITY_ATTRIBUTES* useDefaultSecurity = NULL;
				DWORD onlySucceedIfFileExists = OPEN_EXISTING;
				DWORD useDefaultAttributes = FILE_ATTRIBUTE_NORMAL;
				HANDLE dontUseTemplateFile = NULL;
				fileHandle = CreateFile( fileName, desiredAccess, otherProgramsCanStillReadTheFile,
					useDefaultSecurity, onlySucceedIfFileExists, useDefaultAttributes, dontUseTemplateFile );
				if ( fileHandle == INVALID_HANDLE_VALUE )
				{
					LogMessage( std::string( "Failed to open fragment shader " ) + fileName );
					return false;
				}
			}
			// Get the file's size
			DWORD fileSize;
			{
				LARGE_INTEGER fileSize_integer;
				if ( GetFileSizeEx( fileHandle, &fileSize_integer ) == TRUE )
				{
					// This is unsafe, because the file's size could be bigger than a DWORD
					fileSize = static_cast<DWORD>( fileSize_integer.QuadPart );
				}
				else
				{
					LogMessage( std::string( "Couldn't get the size of fragment shader " ) + fileName );
					CloseHandle( fileHandle );
					return false;
				}
			}
			// Read the file's contents into temporary memory
			compiledFragmentShader = malloc( fileSize );
			{
				DWORD bytesReadCount;
				OVERLAPPED* readSynchronously = NULL;
				if ( ReadFile( fileHandle, compiledFragmentShader, fileSize,
					&bytesReadCount, readSynchronously ) == TRUE )
				{
					CloseHandle( fileHandle );
				}
				else
				{
					LogMessage( std::string( "Couldn't read the contents of fragment shader " ) + fileName );
					free( compiledFragmentShader );
					CloseHandle( fileHandle );
					return false;
				}
			}
		}


	HRESULT result = m_direct3dDevice->CreatePixelShader( reinterpret_cast<DWORD*>( compiledFragmentShader ), &m_scene.fragmentShader );
	if ( SUCCEEDED( result ) )
		{
				// Get the constant table from the fragment shader
				result = D3DXGetShaderConstantTable( reinterpret_cast<DWORD*>( compiledFragmentShader ), &m_scene.fragmentShaderConstantTable );
				if ( SUCCEEDED( result ) )
				{
					// Set the default values
					result = m_scene.fragmentShaderConstantTable->SetDefaults( m_direct3dDevice );
					if ( FAILED( result ) )
					{
						LogMessage( "Couldn't set the fragment shader constant defaults" );
					}
				}
				free( compiledFragmentShader );
				if ( FAILED( result ) )
				{
					LogMessage( "Couldn't get the fragment shader constant table" );
					return false;
				}
			}
			else
			{
				LogMessage( "Couldn't create the fragment shader object" );
				free( compiledFragmentShader );
				return false;
			}
	return true;
}


bool Effect::Release()
{
	bool wereThereAnyErrors = false;

	if ( m_scene.fragmentShaderConstantTable )
	{
		m_scene.fragmentShaderConstantTable->Release();
		m_scene.fragmentShaderConstantTable = NULL;
	}
	if ( m_scene.fragmentShader )
	{
		m_scene.fragmentShader->Release();
		m_scene.fragmentShader = NULL;
	}
	if ( m_scene.vertexShaderConstantTable )
	{
		m_scene.vertexShaderConstantTable->Release();
		m_scene.vertexShaderConstantTable = NULL;
	}
	if ( m_scene.vertexShader )
	{
		m_scene.vertexShader->Release();
		m_scene.vertexShader = NULL;
	}
	
	return !wereThereAnyErrors;
}


  char * Effect::getVertexShader()
  {
	  return vertexShaderFile;
  }


		
   char *Effect::getFragmentShader()
  {
	return fragmentShaderFile;
  }

   char *Effect::getBlending()
  {
	return blending;
  }
   
}

