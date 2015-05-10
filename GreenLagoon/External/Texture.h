#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "IReferenceCounted.h"

namespace Cheesy
{

class Texture : public IReferenceCounted
{
	void *						m_pData;

	Texture( void * i_pData );
	~Texture();

public:
	void Activate( unsigned int i_Stage );
	static Texture * CreateFromData( void * i_pData, unsigned int i_DataSizeB );

};

} // namespace Cheesy

#endif // __TEXTURE_H