// Header Files
//=============

#include "cEntityBuilder.h"

// Inherited Implementation
//=========================

bool cs6963::cEntityBuilder::Build_derived( const char* i_fileName_source, const char* i_fileName_target ) const
{
	// For now effects don't get "built";
	// instead, copy the source entity as-is to the target
	BOOL shouldFailIfDestinationFileAlreadyExists = FALSE;
	if ( CopyFile( i_fileName_source, i_fileName_target, shouldFailIfDestinationFileAlreadyExists ) == TRUE )
	{
		return true;
	}
	else
	{
		std::string errorMessage = std::string( "Couldn't copy " ) + i_fileName_source + " to " + i_fileName_target + ":  "
			+ GetLastWindowsError();
		FormatAndOutputErrorMessage( errorMessage );
		return false;
	}
}
