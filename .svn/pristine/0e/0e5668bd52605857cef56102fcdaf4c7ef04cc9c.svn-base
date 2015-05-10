#include"MemoryPool.h"

  static Engine::BitPool<int> *myBitPool=NULL;
   void *current_ptr;
   void *start_ptr;


Engine::MemoryPool* Engine::MemoryPool::CreateMemoryPool(const unsigned int item_size,const unsigned int item_count)
{
	
	
    if(myBitPool==NULL)
	 {
	     myBitPool=Engine::BitPool<int>::CreateBitPool(100);
	     printf("\nBit pool of size 100 Bits created");
	 }

	start_ptr=(_aligned_malloc( (item_size*item_count),CACHE_LINE ) );
	assert(start_ptr);

	MemoryPool *myMem=reinterpret_cast<MemoryPool*>(start_ptr);
	return myMem;
}


void * Engine::MemoryPool::alloc(const unsigned int item_count)
{
	//Searching next clear bit
    int bit=myBitPool->nextClearBit();

	if(bit==-1)
	  printf("\nMemoryPool is full. Following Vector created maybe corrupt:");
	else
	  //setting it to 1;locking it for storing vector
	  myBitPool->setBit(bit);
	
	//Pointer calculation pointing at next free location 
	unsigned int ptr_calc=(unsigned int)start_ptr+(bit*(item_count*sizeof(Vector3)) );
	current_ptr=reinterpret_cast<void *>(ptr_calc);
	return current_ptr;
}

void Engine::MemoryPool::DestroyMemoryPool()
{
	myBitPool->DestroyBitPool(myBitPool);


	if(start_ptr)
	_aligned_free(start_ptr );

	start_ptr=NULL;
	current_ptr=NULL;
}

void Engine::MemoryPool::freeSpace(const unsigned int Freebit)
{ 
	myBitPool->clearBit(Freebit);
}