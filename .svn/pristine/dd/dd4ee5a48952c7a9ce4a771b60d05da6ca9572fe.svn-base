/*
	This class defines the main application window
*/

#ifndef CS6963_CMAINWINDOW_H
#define CS6963_CMAINWINDOW_H

// Header Files
//=============

#include "Initialization.h"

#include "cRenderer.h"

// Class Definition
//=================

namespace cs6963
{
	class cMainWindow
	{
		// Interface
		//==========

	public:

		// Singleton Access
		//-----------------

		static inline cMainWindow& GetSingleton()
		{
			static cMainWindow singleton;
			return singleton;
		}
		#define g_mainWindow cs6963::cMainWindow::GetSingleton()

		// Access
		//-------

		HWND GetHandle() const;

		// Initialization / Shutdown
		//--------------------------

		bool Initialize( const HINSTANCE i_thisInstanceOfTheApplication, HWND window );
		int WaitForShutdown() const;
		~cMainWindow();

		// Data
		//=====
	public:
	    cRenderer m_renderer;

	private:

		HINSTANCE m_applicationInstance;
		ATOM m_class;
		HWND m_window;

		static const char* m_sClassName;

		// Implementation
		//===============

	private:

		// Initialization / Shutdown
		//--------------------------

		cMainWindow();
		bool Create( const int i_initialWindowDisplayState );
		bool Destroy();
		bool RegisterClass();
		bool UnregisterClass();
		

		// Callbacks
		//----------

		static LRESULT CALLBACK OnMessageReceived( HWND i_window, UINT i_message, WPARAM i_wParam, LPARAM i_lParam );

	};
}

#endif	// CS6963_CMAINWINDOW_H
