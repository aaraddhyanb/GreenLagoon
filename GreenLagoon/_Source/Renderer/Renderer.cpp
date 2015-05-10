#include"Renderer.h"

namespace Engine{


// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void Renderer::Init(HINSTANCE i_thisInstanceOfTheApplication, HINSTANCE i_thisIsNothing, char* i_commandLineArguments, int i_initialWindowDisplayState)
{
	WNDCLASSEX wc;
    MSG Msg;
	
	//Name the window class
    const char g_szClassName[] = "Capture The Flag";

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = i_thisInstanceOfTheApplication;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Capture The Flag",
        WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, i_thisInstanceOfTheApplication, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    ShowWindow(hwnd, i_initialWindowDisplayState);
	
    //UpdateWindow(hwnd);  
	int something= cs6963::Create(hwnd,i_thisInstanceOfTheApplication,  i_thisIsNothing,  i_commandLineArguments,  i_initialWindowDisplayState);

	  //  struct Cheesy::Point2D		center( 0.0f, 0.0f );
	//	struct Cheesy::Point2D		size( 50.0f, 50.0f );
	//	struct Cheesy::Point2D		offsetGG( 50.0f, 100.0f );
	//	struct Cheesy::Point2D		offsetBG( 0.0f, 0.0f );

	//	struct Cheesy::ColorRGBA	white( 255, 255, 255, 255 );
	//	Cheesy::UVSet				UVs = { Cheesy::UV( 0.0f, 0.0f ), Cheesy::UV( 1.0f, 0.0f ), Cheesy::UV( 0.0f, 1.0f ), Cheesy::UV( 1.0f, 1.0f ) };
	//    struct Cheesy::ColorRGBA ClearColor( 50, 50, 255, 0 );

	/*	  config_t cfg;
		  const char *playerImage;
          const char *monsterImage;

		  config_init(&cfg);
		  if(! config_read_file(&cfg, "config.cfg"))
		  {
			fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
				            config_error_line(&cfg), config_error_text(&cfg));
			config_destroy(&cfg);
		  }

		  config_lookup_string(&cfg, "PlayerImage", &playerImage);
		  config_lookup_string(&cfg, "MonsterImage", &monsterImage);

		Cheesy::Texture * pSampleTexture = CreateTextureFromFile( playerImage );
		assert( pSampleTexture );
		

		pGoodGuy = Cheesy::Sprite::Create( center, 0.1f, size, white, *pSampleTexture, UVs );
		assert( pGoodGuy );

		pSampleTexture->Release();

		pSampleTexture = CreateTextureFromFile(monsterImage );
		assert( pSampleTexture );

		pBadGuy = Cheesy::Sprite::Create( center, 0.1f, size, white, *pSampleTexture, UVs );
		assert( pBadGuy );

		pSampleTexture->Release();
	
	    config_destroy(&cfg);*/

		m_SharedPtr.clear();
}


void Renderer::AddActor(SharedPointer<Actor> &i_instance)
{
	SharedPointer<Actor> *sharedPtr= new SharedPointer<Actor>(i_instance);
	m_SharedPtr.push_back(sharedPtr);

}


void Renderer::RemoveActor(Actor &i_instance)
{
	 unsigned int id=i_instance.getID();

	for(unsigned int i=0; i<m_SharedPtr.size(); i++)
	{
		if(id== (*m_SharedPtr[i])->getID() )
		{
			 delete m_SharedPtr[i];
			for(unsigned int j=i; j< m_SharedPtr.size()-1; j++)
			{
			     m_SharedPtr.at(j)=m_SharedPtr.at(j+1);
			}
			
			 m_SharedPtr.pop_back();
		     break;
		}

	}

}

void Renderer::Update(float deltaTime)
{
	 cs6963::Update(); 
	 int f=8;
	/* struct Cheesy::ColorRGBA ClearColor( 80,80,80,0 );


	   Cheesy::BeginFrame(ClearColor);
    for(unsigned int i=0; i<m_SharedPtr.size();i++)
	{
		struct Cheesy::Point2D position( (*m_SharedPtr[i])->getActorPosition()->getx(),(*m_SharedPtr[i])->getActorPosition()->gety() );
			
		if( (*m_SharedPtr[i])->getID()==0)
			pGoodGuy->Draw( position, (*m_SharedPtr[i])->getActorRotation() );
		else
			pBadGuy->Draw( position, (*m_SharedPtr[i])->getActorRotation());

	}
	
	Cheesy::EndFrame();*/
}


/*Cheesy::Texture * CreateTextureFromFile( const char * i_pTextureFilename )
{
	assert( i_pTextureFilename != NULL );

	FILE * pFile = NULL; 

	errno_t fopenError = fopen_s( &pFile, i_pTextureFilename, "rb" );
	if( fopenError != 0 )
		return NULL;

	assert( pFile != NULL );

	int FileIOError = fseek( pFile, 0, SEEK_END );
	assert( FileIOError == 0 );

	long FileSize = ftell( pFile );
	assert( FileSize >= 0 );

	FileIOError = fseek( pFile, 0, SEEK_SET );
	assert( FileIOError == 0 );

	char * pBuffer = new char[FileSize];
	assert( pBuffer );

	long FileRead = fread( pBuffer, 1, FileSize, pFile );
	assert( FileRead == FileSize );

	fclose( pFile );

	Cheesy::Texture * pTexture = Cheesy::Texture::CreateFromData( pBuffer, FileSize );

	delete [] pBuffer;

	return pTexture;
}
*/
void Renderer::Shutdown()
{
	
	//delete pGoodGuy;
	//delete pBadGuy;
	//Cheesy::Shutdown();

	for(unsigned int i=0; i< m_SharedPtr.size(); i++)
	{
		delete m_SharedPtr[i];
	}
			
		  
	m_SharedPtr.erase(m_SharedPtr.begin(),m_SharedPtr.end());
	
}

} //namespace end
