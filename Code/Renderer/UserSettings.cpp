// Header Files
//=============

#include "UserSettings.h"

#include <cmath>
#include <sstream>
#include <string>

extern "C"
{
	#include "../External/Lua/5.2.1/lua.h"
	#include "../External/Lua/5.2.1/lauxlib.h"
}

// Static Data Initialization
//===========================

namespace
{
	unsigned int s_height = 900;
	bool s_isFullScreenModeEnabled = false;
	unsigned int s_width = 1700;

	const char* s_userSettingsfileName = "settings.ini";
}

// Helper Function Declarations
//=============================

namespace
{
	bool IsNumberAnInteger( const lua_Number i_number );
	bool LoadUserSettingsIntoLuaTable( lua_State& io_luaState, bool& o_doesUserSettingsFileExist );
	bool PopulateUserSettingsFromLuaTable( lua_State& io_luaState );
}

// Interface
//==========

unsigned int cs6963::UserSettings::GetHeight()
{
	return s_height;
}

unsigned int cs6963::UserSettings::GetWidth()
{
	return s_width;
}

 unsigned int cs6963::UserSettings::IsFullScreenModeEnabled()
{
	return s_isFullScreenModeEnabled;
}

bool cs6963::UserSettings::Initialize()
{
	LogMessage( "Initializing user settings" );
	bool didInitializationSucceed = true;

	// Create a new Lua state
	lua_State* luaState = NULL;
	bool wasUserSettingsEnvironmentCreated = false;
	{
		luaState = luaL_newstate();
		if ( luaState == NULL )
		{
			LogMessage( "Memory allocation error while creating new Lua state!" );
			didInitializationSucceed = false;
			goto CleanUp;
		}
	}
	// Create an empty table to be used as the Lua environment for the user settings
	{
		lua_newtable( luaState );
		wasUserSettingsEnvironmentCreated = true;
	}
	// Load the user settings
	bool doesUserSettingsFileExist;
	if ( LoadUserSettingsIntoLuaTable( *luaState, doesUserSettingsFileExist ) )
	{
		if ( doesUserSettingsFileExist )
		{
			// Populate the user settings in C from the user settings in the Lua environment
			if ( !PopulateUserSettingsFromLuaTable( *luaState ) )
			{
				didInitializationSucceed = false;
				goto CleanUp;
			}
		}
	}
	else
	{
		didInitializationSucceed = false;
		goto CleanUp;
	}

	// Free the Lua environment

CleanUp:

	if ( luaState )
	{
		if ( wasUserSettingsEnvironmentCreated )
		{
			lua_pop( luaState, 1 );
		}
		// Sanity Check
		{
			int stackItemCount = lua_gettop( luaState );
			if ( stackItemCount != 0 )
			{
				std::ostringstream errorMessage;
				errorMessage << "There are still " << stackItemCount
					<< " items in the Lua stack when the Lua state is being closed";
				LogMessage( errorMessage.str() );
				didInitializationSucceed = false;
			}
		}
		lua_close( luaState );
	}

	return didInitializationSucceed;
}

// Helper Function Definitions
//============================

namespace
{
	bool IsNumberAnInteger( const lua_Number i_number )
	{
		lua_Number integralPart;
		lua_Number fractionalPart = modf( i_number, &integralPart );
		return integralPart == i_number;
	}

	bool LoadUserSettingsIntoLuaTable( lua_State& io_luaState, bool& o_doesUserSettingsFileExist )
	{
		// Load the file into a Lua function
		int result = luaL_loadfile( &io_luaState, s_userSettingsfileName );
		if ( result == LUA_OK )
		{
			o_doesUserSettingsFileExist = true;

			// Set the Lua function's environment
			{
				lua_pushvalue( &io_luaState, -2 );
				const char* upValueName = lua_setupvalue( &io_luaState, -2, 1 );
				if ( upValueName == NULL )
				{
					std:: string errorMessage = std::string( "Internal error setting the Lua environment for " )
						+ s_userSettingsfileName + "... This should never happen";
					cs6963::LogMessage( errorMessage );
					lua_pop( &io_luaState, 2 );
					return false;
				}
			}
			// Call the Lua function
			{
				int noArguments = 0;
				int noReturnValues = 0;
				int noErrorMessageHandler = 0;
				result = lua_pcall( &io_luaState, noArguments, noReturnValues, noErrorMessageHandler );
				if ( result == LUA_OK )
				{
					return true;
				}
				else
				{
					std::string luaErrorMessage( lua_tostring( &io_luaState, -1 ) );
					lua_pop( &io_luaState, 1 );

					if ( result == LUA_ERRRUN )
					{
						std::string errorMessage = std::string( "Error in " )
							+ s_userSettingsfileName + ": " + luaErrorMessage;
						cs6963::LogMessage( errorMessage );
					}
					else
					{
						std::string errorMessage = std::string( "Error processing user settings file: " )
							+ luaErrorMessage;
						cs6963::LogMessage( errorMessage );
					}

					return false;
				}
			}
		}
		else
		{
			o_doesUserSettingsFileExist = false;

			std::string luaErrorMessage( lua_tostring( &io_luaState, -1 ) );
			lua_pop( &io_luaState, 1 );

			if ( result == LUA_ERRFILE )
			{
				// If loading the file failed because the file doesn't exist it's ok
				if ( GetFileAttributes( s_userSettingsfileName ) == INVALID_FILE_ATTRIBUTES )
				{
					std::string message = std::string( "User settings file \"" )
						+ s_userSettingsfileName + "\" doesn't exist; default settings will be used";
					cs6963::LogMessage( message );
					return true;
				}
				else
				{
					std::string errorMessage = std::string( "User settings file " )
						+ s_userSettingsfileName + " exists but couldn't be opened or read: "
						+ luaErrorMessage;
					cs6963::LogMessage( errorMessage );
				}
			}
			else if ( result == LUA_ERRSYNTAX )
			{
				std::string errorMessage = std::string( "Syntax error in " )
					+ s_userSettingsfileName + ": " + luaErrorMessage;
				cs6963::LogMessage( errorMessage );
			}
			else
			{
				std::string errorMessage = std::string( "Error loading user settings file: " )
					+ luaErrorMessage;
				cs6963::LogMessage( errorMessage );
			}

			return false;
		}
	}

	bool PopulateUserSettingsFromLuaTable( lua_State& io_luaState )
	{
		// Full-Screen Mode
		{
			const char* key_isEnabled = "isFullScreenModeEnabled";

			lua_pushstring( &io_luaState, key_isEnabled );
			lua_gettable( &io_luaState, -2 );
			if ( lua_isboolean( &io_luaState, -1 ) )
			{
				s_isFullScreenModeEnabled = lua_toboolean( &io_luaState, -1 ) != 0;
				if ( s_isFullScreenModeEnabled )
				{
					cs6963::LogMessage( "Rendering in full-screen mode" );
				}
				else
				{
					cs6963::LogMessage( "Rendering in windowed mode" );
				}
			}
			else if ( lua_isnil( &io_luaState, -1 ) )
			{
				std::ostringstream message;
				message << "No value for whether full-screen mode is enabled (\""
					<< key_isEnabled << "\") was found in " << s_userSettingsfileName
					<< "; using the default "
					<< ( s_isFullScreenModeEnabled ? "full-screen" : "windowed" ) << " mode";
				cs6963::LogMessage( message.str() );
			}
			else
			{
				std::string errorMessage = std::string( "The value of \"" )
					+ key_isEnabled + "\" specified in " + s_userSettingsfileName
					+ " must be a boolean (instead of a " + luaL_typename( &io_luaState, -1 ) + ")";
				cs6963::LogMessage( errorMessage );
				lua_pop( &io_luaState, 1 );
				return false;
			}
			lua_pop( &io_luaState, 1 );
		}

		// Width
		{
			const char* key_width = "width";

			lua_pushstring( &io_luaState, key_width );
			lua_gettable( &io_luaState, -2 );
			if ( lua_isnumber( &io_luaState, -1 ) )
			{
				lua_Number floatingPointResult = lua_tonumber( &io_luaState, -1 );
				if ( IsNumberAnInteger( floatingPointResult ) )
				{
					if ( floatingPointResult >= lua_Number( 0 ) )
					{
						s_width = static_cast<unsigned int>( floatingPointResult );
						std::ostringstream message;
						message << "Width: " << s_width;
						cs6963::LogMessage( message.str() );
					}
					else
					{
						std::ostringstream errorMessage;
						errorMessage << "The value of \"" << key_width
							<< "\" specified in " << s_userSettingsfileName
							<< " must be a non-negative integer (instead of "
							<< floatingPointResult << ")";
						cs6963::LogMessage( errorMessage.str() );
						lua_pop( &io_luaState, 1 );
						return false;
					}
				}
				else
				{
					std::ostringstream errorMessage;
					errorMessage << "The value of \"" << key_width
						<< "\" specified in " << s_userSettingsfileName
						<< " must be an integer value (instead of "
						<< floatingPointResult << ")";
					cs6963::LogMessage( errorMessage.str() );
					lua_pop( &io_luaState, 1 );
					return false;
				}
			}
			else if ( lua_isnil( &io_luaState, -1 ) )
			{
				std::ostringstream message;
				message << "No value for the width to render at (\""
					<< key_width << "\") was found in " << s_userSettingsfileName
					<< "; using the default of " << s_width;
				cs6963::LogMessage( message.str() );
			}
			else
			{
				std::string errorMessage = std::string( "The value of \"" )
					+ key_width + "\" specified in " + s_userSettingsfileName
					+ " must be an integer (instead of a " + luaL_typename( &io_luaState, -1 ) + ")";
				cs6963::LogMessage( errorMessage );
				lua_pop( &io_luaState, 1 );
				return false;
			}
			lua_pop( &io_luaState, 1 );
		}
		// Height
		{
			const char* key_height = "height";

			lua_pushstring( &io_luaState, key_height );
			lua_gettable( &io_luaState, -2 );
			if ( lua_isnumber( &io_luaState, -1 ) )
			{
				lua_Number floatingPointResult = lua_tonumber( &io_luaState, -1 );
				if ( IsNumberAnInteger( floatingPointResult ) )
				{
					if ( floatingPointResult >= lua_Number( 0 ) )
					{
						s_height = static_cast<unsigned int>( floatingPointResult );
						std::ostringstream message;
						message << "Height: " << s_height;
						cs6963::LogMessage( message.str() );
					}
					else
					{
						std::ostringstream errorMessage;
						errorMessage << "The value of \"" << key_height
							<< "\" specified in " << s_userSettingsfileName
							<< " must be a non-negative integer (instead of "
							<< floatingPointResult << ")";
						cs6963::LogMessage( errorMessage.str() );
						lua_pop( &io_luaState, 1 );
						return false;
					}
				}
				else
				{
					std::ostringstream errorMessage;
					errorMessage << "The value of \"" << key_height
						<< "\" specified in " << s_userSettingsfileName
						<< " must be an integer value (instead of "
						<< floatingPointResult << ")";
					cs6963::LogMessage( errorMessage.str() );
					lua_pop( &io_luaState, 1 );
					return false;
				}
			}
			else if ( lua_isnil( &io_luaState, -1 ) )
			{
				std::ostringstream message;
				message << "No value for the height to render at (\""
					<< key_height << "\") was found in " << s_userSettingsfileName
					<< "; using the default of " << s_height;
				cs6963::LogMessage( message.str() );
			}
			else
			{
				std::string errorMessage = std::string( "The value of \"" )
					+ key_height + "\" specified in " + s_userSettingsfileName
					+ " must be an integer (instead of a " + luaL_typename( &io_luaState, -1 ) + ")";
				cs6963::LogMessage( errorMessage );
				lua_pop( &io_luaState, 1 );
				return false;
			}
			lua_pop( &io_luaState, 1 );
		}

		return true;
	}
}
