/*
	This class defines the renderer class
*/

#ifndef CS6963_CRENDERER_H
#define CS6963_CRENDERER_H

// Header Files
//=============

#include "Scene.h"
#include "Initialization.h"
#include "TextField.h"
#include "Slider.h"

// Class Definition
//=================

namespace cs6963
{

	class cRenderer
	{
		
		private:

		IDirect3D9* m_direct3dInterface;
		
		IDirect3DDevice9* m_direct3dDevice;

		bool ReleaseScene();

		std::vector<TextField *> allTextFields;
		std::vector<Slider *> allSliders;

	   public:
		 
		static float scoreLabel;

		void AddText(TextField *text,LPCSTR i_text, int x, int y, float (*func)(void));
		void AddSlider(Slider *musicVolume,LPCSTR i_text, int x, int y, int minX, int maxX, void (*func)(float));

	     Scene *scene;
		 static unsigned char red;
		 static bool hideObject;
		 unsigned char green;
	     unsigned char blue;
	
		void Update() const;

		// Initialization / Shutdown
		//--------------------------

		cRenderer();
		bool Initialize(HWND window);

		~cRenderer();
		bool Shutdown();
	
	    static void SetScoreLabel(float score);
		static void hideObj(bool status);
	    static void colorRed(float i_red);
		void colorGreen(float i_green);
		void colorBlue(float i_blue);
		static float DisplayScore(void);
	};
}



#endif	// CS6963_CRENDERER_H
