/*
	This class builds materials
*/

#ifndef CS6963_CCUBEMAPSBUILDER_H
#define CS6963_CCUBEMAPSBUILDER_H

// Header Files
//=============

#include "../GenericBuilder/cbGenericBuilder.h"

// Class Definition
//=================

namespace cs6963
{
	class cCubeMapsBuilder : public cbGenericBuilder
	{
		// Inherited Interface
		//====================

	private:

		virtual const char* GetToolName() const { return "CubeMapsBuilder"; }

		// Inherited Implementation
		//=========================

	private:

		virtual bool Build_derived( const char* i_fileName_source, const char* i_fileName_target ) const;
	};
}

#endif	// CS6963_CCUBEMAPSBUILDER_H
