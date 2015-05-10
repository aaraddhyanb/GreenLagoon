#ifndef __CHEESY_H
#define __CHEESY_H

#include "Types.h"

namespace Cheesy
{
	typedef void (*keyCallback)( unsigned int i_CharID );

	bool Create( const char * i_pAppName, unsigned int i_WindowWidth, unsigned int i_WindowHeight, bool i_DebugVS = false, bool i_DebugPS = false );
	
	bool Service( bool & o_bQuitRequested );

	bool BeginFrame( const ColorRGBA & i_FrameClearColor );
	bool EndFrame( void );
	
	bool DrawQuad( const struct Point2D & i_center, float i_width, float i_height, float i_depth, const struct ColorRGB & i_color );

	void setKeyDownCallback( keyCallback i_Callback );
	void setKeyPressCallback( keyCallback i_Callback );

	int GetExitCode( void );
	void Shutdown( void );
} ;

#endif // __CHEESY_H