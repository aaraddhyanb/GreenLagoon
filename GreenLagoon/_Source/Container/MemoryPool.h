#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include"BitPool.h"
#include"Vector3.h"

#define CACHE_LINE 64

namespace Engine
{
	class MemoryPool
	{

	private:

		//non-copyable
		MemoryPool(const unsigned int item_size, const unsigned int item_count );
		void operator =(const MemoryPool &value);

	public:
		//MemoryPool(void){};
		//MemoryPool(unsigned int item_size, unsigned int item_count);

		static MemoryPool* CreateMemoryPool(const unsigned int item_size, const unsigned int item_count);
		static void DestroyMemoryPool();
		void *alloc(const unsigned int item_count);
	    void freeSpace(const unsigned int bit);
	};

}



#endif 

