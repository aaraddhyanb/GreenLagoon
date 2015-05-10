#ifdef _WIN64
   //define something for Windows (64-bit)
#include "Target_WIN64.h"
#elif _WIN32
   //define something for Windows (32-bit)
#include "Target_WIN32.h"
#elif __APPLE__
    #if TARGET_OS_IPHONE    
         // iOS device
    #elif TARGET_IPHONE_SIMULATOR
        // iOS Simulator
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        // Unsupported platform
    #endif
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif


// brief		Prints to debug output based on debuglevel
// Eg:
#if defined _DEBUG
#define DEBUG_PRINT(debugLevel,fmt,...) r3al1ty::ConsolePrint(debugLevel,fmt,__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif