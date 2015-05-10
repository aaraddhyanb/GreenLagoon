#ifndef __I_REFERENCE_COUNTED_H
#define __I_REFERENCE_COUNTED_H

#include <assert.h>

namespace Cheesy
{

class IReferenceCounted
{
	mutable unsigned int		i_RefCount;

protected:
	virtual ~IReferenceCounted() = 0 { }

public:
	IReferenceCounted() : i_RefCount( 1 )
	{
	}

	void Acquire() const
	{ 
		i_RefCount++; 
	}

	unsigned int Release() const
	{
		assert( i_RefCount > 0 );

		unsigned int newRefCount = --i_RefCount;

		if( newRefCount == 0 )
			delete this;

		return newRefCount;
	}
} ;

} // namespace Cheesy

#endif // __I_REFERENCE_COUNTED_H