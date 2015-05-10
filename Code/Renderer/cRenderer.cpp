// H11eader Files
//=============

#include "cRenderer.h"
#include "cMainWindow.h"
#include "RendererWidgets.h"

#include <d3d9.h>
#include <D3DX9Shader.h>

using namespace std;

bool  cs6963::cRenderer::hideObject=false;
unsigned char cs6963::cRenderer::red=0;
float  cs6963::cRenderer::scoreLabel=0;

// Render
//-------
cs6963::cRenderer::cRenderer()
	:
    m_direct3dInterface( NULL ), m_direct3dDevice( NULL )
	
  {
	 scene= new Scene();
  }


float cs6963::cRenderer:: DisplayScore(void)
{
	return cs6963::cRenderer::scoreLabel;
}


float fpsDisplay(void)
{
	float fps=60.0f;
	return fps;
}

void wireframe(bool status)
{
	cs6963::cMesh::WireMode(status);
}

void debugLines(bool status)
{
	cs6963::Octree::showDebugLines=status;
}

// Initialization 
//--------------------------

bool cs6963::cRenderer::Initialize(HWND window)
{
	// Initialize the interface to the Direct3D9 library
	{
		// D3D_SDK_VERSION is #defined by the Direct3D header files,
		// and is just a way to make sure that everything is up-to-date
		m_direct3dInterface = Direct3DCreate9( D3D_SDK_VERSION );
		if ( m_direct3dInterface )
		{
			LogMessage( "Created a Direct3D9 interface" );
		}
		else
		{
			LogMessage( "Failed to create a Direct3D9 interface" );
			return false;
		}
	}

	// Create an interface to a Direct3D device
	{
		UINT useDefaultDevice = D3DADAPTER_DEFAULT;
		D3DDEVTYPE useHardwareRendering = D3DDEVTYPE_HAL;
		HWND renderInMainWindow = window;
		DWORD useHardwareVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		D3DPRESENT_PARAMETERS presentationParameters = { 0 };
		{
			presentationParameters.BackBufferWidth = UserSettings::GetWidth();
			presentationParameters.BackBufferHeight = UserSettings::GetHeight();
			presentationParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
			presentationParameters.BackBufferCount = 1;
			presentationParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
			presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
			presentationParameters.hDeviceWindow =window;
			presentationParameters.Windowed = UserSettings::IsFullScreenModeEnabled() ? FALSE : TRUE;
			presentationParameters.EnableAutoDepthStencil = TRUE;
			presentationParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
			presentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		}
		
		HRESULT result = m_direct3dInterface->CreateDevice( useDefaultDevice, useHardwareRendering,
			renderInMainWindow, useHardwareVertexProcessing, &presentationParameters, &m_direct3dDevice );
		if ( SUCCEEDED( result ) )
		{
			LogMessage( "Created a Direct3D device" );
		}
		else
		{
			LogMessage( "Failed to create a Direct3D device" );
			return false;
		}
	}
	 
	  
	  scene->Initialize(m_direct3dDevice,m_direct3dInterface);

	  scene->getScene();

	  //Initialize Debug Widgets
#ifdef _DEBUG
	  {
		  RendererWidgets::Singleton().init(m_direct3dDevice);
		  RendererWidgets::Singleton().AddTextField("FPS:", 100, 150, &fpsDisplay);
		  RendererWidgets::Singleton().AddCheckBox("Wireframe Mode", 100, 200, &wireframe);
		  RendererWidgets::Singleton().AddSlider("Red Color",100, 250, 0, 255, &colorRed);
		  RendererWidgets::Singleton().AddCheckBox("Debug lines", 100, 310, &debugLines);
	  }
#endif
	 
		return true;

}

void cs6963::cRenderer::SetScoreLabel(float score)
{
	scoreLabel=score;
}

void cs6963::cRenderer::hideObj(bool status)
{
	hideObject=status;
}

void cs6963::cRenderer::colorRed(float i_red)
{
	red=i_red;
}


void cs6963::cRenderer::colorGreen(float i_green)
{
	green=255;
}


void cs6963::cRenderer::colorBlue(float i_blue)
{
	blue=255;
}

void cs6963::cRenderer::AddText(TextField *text,LPCSTR i_text, int x, int y, float (*func)(void))
{
	text->init(m_direct3dDevice,i_text, x, y, func);
	allTextFields.push_back(text);
}

void cs6963::cRenderer::AddSlider(Slider *slideOpt,LPCSTR i_text, int x, int y, int minX, int maxX, void (*func)(float))
{
	slideOpt->init(m_direct3dDevice,i_text, x, y,minX, maxX, func);
	allSliders.push_back(slideOpt);
}

void cs6963::cRenderer::Update() const
{
	
	
	// Every frame an entirely new image will be created.
	// Before drawing anything, then, the previous image will be erased
	// by "clearing" the image buffer (filling it with a solid color)
	{
		const D3DRECT* subRectanglesToClear = NULL;
		DWORD subRectangleCount = 0;
		DWORD clearTheRenderTarget = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		D3DCOLOR clearColor;
		{
			// Usually black is used:
			clearColor = D3DCOLOR_XRGB( red, green ,blue );
			// To show how often the screen is updated, however,
			// the clear color can be changed every frame:
			{
			/*
				// (Don't worry if the code in this block seems strange;
				// it's just a quick and dirty way to change colors every frame)
				static unsigned char red = 0;
				static unsigned char green = 0;
				static unsigned char blue = 0;

				red += 7;
				green -= 4;
				blue += 1;

				clearColor = D3DCOLOR_XRGB( red, green, blue );
			*/
			}
		}
		float clearZBuffer = 1.0f;
		DWORD noStencilBuffer = 0;
		HRESULT result = m_direct3dDevice->Clear( subRectangleCount, subRectanglesToClear,
			clearTheRenderTarget, clearColor, clearZBuffer, noStencilBuffer );
		assert( SUCCEEDED( result ) );
	}

	if(!hideObject)
	{
		scene->Update();
	}
	
	//Debug Widgets
#ifdef _DEBUG
	{
		RendererWidgets::Singleton().update();
		RendererWidgets::Singleton().draw();
	}
#endif

	for(int i=0; i< allTextFields.size(); ++i)
	{
		allTextFields[i]->draw();
	}

	for(int i=0; i< allSliders.size(); ++i)
	{
		allSliders[i]->draw();
	}


	//score

	//m_labelFont->DrawText(NULL, (LPCSTR)scoreLabel.c_str(), -1, &, 0, D3DCOLOR(255));

	// Everything has been drawn to the "back buffer", which is just an image in memory.
	// In order to display it, the contents of the back buffer must be "presented"
	// (to the front buffer)
	{
		const RECT* noSourceRectangle = NULL;
		const RECT* noDestinationRectangle = NULL;
		HWND useDefaultWindow = NULL;
		const RGNDATA* noDirtyRegion = NULL;
		HRESULT result = m_direct3dDevice->Present( noSourceRectangle, noDestinationRectangle, useDefaultWindow, noDirtyRegion );
		assert( SUCCEEDED( result ) );
	}
}




cs6963::cRenderer::~cRenderer()
{
	Shutdown();
}

bool cs6963::cRenderer::Shutdown()
{
	bool wereThereAnyErrors = false;


/*	if ( !m_effect[i]->Release() )
	{
		wereThereAnyErrors = true;
	}*/

	/*if ( m_vertexDeclaration )
	{
		m_vertexDeclaration->Release();
		m_vertexDeclaration = NULL;
		LogMessage( "Released the vertex declaration" );
	} */

	if ( m_direct3dDevice )
	{
		m_direct3dDevice->Release();
		m_direct3dDevice = NULL;
		LogMessage( "Released the Direct3D device" );
	}

	if ( m_direct3dInterface )
	{
		m_direct3dInterface->Release();
		m_direct3dInterface = NULL;
		LogMessage( "Released the Direct3D9 interface" );
	}

	return !wereThereAnyErrors;
}

