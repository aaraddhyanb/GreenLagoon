#ifndef BITPOOL_H
#define BITPOOL_H

#include<stddef.h>
#include<assert.h>
#include<memory.h>

namespace Engine
{
	
template <typename T>
class BitPool
{
	
private:
	 
	static const unsigned int bitsPerElement= sizeof(T) * 8;

	T  * const pool;
	unsigned int total_bits;
	unsigned int total_elements;

	BitPool(T *elementsArray, const unsigned int &elementsRequired,const unsigned int &item_number);

	//non-copyable
	BitPool(const BitPool &value);
	void operator=(const BitPool &value);

public:
	

	static BitPool * CreateBitPool(const unsigned int item_number);

    const bool isBitSet(const unsigned int bit) const;

    const bool isBitClear(const unsigned int bit) const;
	
	void setBit(const unsigned int bit) const;

	void clearBit(const unsigned int bit);
	
	 const int nextSetBit();
	
    const int nextClearBit();
	
	void DestroyBitPool(BitPool *bitpool);

	//~BitPool()
	//{
	//  
	//	//pool=NULL;
	//	total_bits=0;
	//	total_elements=0;

	//	
	//	bitpool=NULL;

	//}


	
};


} //namespace end


#include "BitPool.inl"

#endif
