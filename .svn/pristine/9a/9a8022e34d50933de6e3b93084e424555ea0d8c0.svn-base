#ifndef _FASTVECTOR_3
#define _FASTVECTOR_3

#include"Vector3.h"
#include"Target.h"


//CACHE_ALIGN_SIZE of myPC is 64 Bytes

namespace Engine
{


CACHE_ALIGN class FastVector3 : public Vector3
{

public:
  
	//Overloading operator new
	void * operator new(size_t size)
	{
	//	printf( "In new constructor %d",size);
		return(_aligned_malloc(size, CACHE_LINE_SIZE));
		
	}

	//Overloading array of operator new
	void * operator  new[](size_t size)
	{
		return (_aligned_malloc(size,CACHE_LINE));

	}

	void operator delete(void *ptr)
	{
		if(ptr!=NULL)
		{

		  printf("\ndeleting single");
		  return (_aligned_free(ptr));
		}

	}

	void operator delete[](void *ptr)
	{
		if(ptr!=NULL)
		{
		  printf("\ndeleting array");
		   return (_aligned_free(ptr));
		}

	}

};


}//namespace end

#include "FastVector3.inl"


#endif