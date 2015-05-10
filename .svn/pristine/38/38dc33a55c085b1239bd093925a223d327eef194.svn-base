#include"EntryPoint.h"

	int Create()
		{
		// Record the date and time that the program was run so that log files can be differentiated
		LogDateAndTime();

		// Load the configurable user settings
		if ( !cs6963::UserSettings::Initialize() )
		{
			return -1;
		}

		// Initialize the timer that will keep track of how much time elapses each frame
		if ( !g_time.Initialize() )
		{
			return -1;
		}

		// All of the work will be done in the context of the main window;
		// it must be initialized with the arguments provided by Windows,
		// and then the program will wait until it shuts down
		// and report the resulting error code back to Windows

		int exitCode;
		if ( g_mainWindow.Initialize( i_thisInstanceOfTheApplication, i_initialWindowDisplayState ) )
		{
			exitCode = g_mainWindow.WaitForShutdown();
		}
		else
		{
			exitCode = -1;
		}

		return exitCode;
		}


		void LogDateAndTime()
		{
			std::string message = "Application started at ";

			// Time
			const int bufferLength = 512;
			char buffer[bufferLength];
			{
				LCID useUsersLocale = LOCALE_USER_DEFAULT;
				DWORD useDefaultFormatOptions = 0;
				const SYSTEMTIME* useCurrentLocalTime = NULL;
				const char* useDefaultFormatPicture = NULL;
				int charactersWrittenToBufferCount = GetTimeFormat(
					useUsersLocale, useDefaultFormatOptions, useCurrentLocalTime, useDefaultFormatPicture, buffer, bufferLength );
				message += charactersWrittenToBufferCount > 0 ? buffer : "unknown time";
			}

			message += " on ";

			// Date
			{
				LCID useUsersLocale = LOCALE_USER_DEFAULT;
				DWORD useDefaultFormatOptions = 0;
				const SYSTEMTIME* useCurrentLocalDate = NULL;
				const char* useDefaultFormatPicture = NULL;
				int charactersWrittenToBufferCount = GetDateFormat(
					useUsersLocale, useDefaultFormatOptions, useCurrentLocalDate, useDefaultFormatPicture, buffer, bufferLength );
				message += charactersWrittenToBufferCount > 0 ? buffer : "unknown date";
			}

			cs6963::LogMessage( message );
		}