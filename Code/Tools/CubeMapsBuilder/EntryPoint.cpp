/*	The main() function in this file is the entry point of this program
*/

// Header Files
//=============

#include "cCubeMapsBuilder.h"

// Entry Point
//============

int main( int i_argumentCount, char** i_arguments )
{
	cs6963::cCubeMapsBuilder mapsBuilder;
	return mapsBuilder.Build( i_argumentCount, i_arguments ) ? 0 : -1;
}
