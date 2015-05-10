
#include<stdio.h>
#include<conio.h>
#include"Util.h"

    template<typename T>
    Engine::BitPool<T>::BitPool(T *elementsArray, const unsigned int &elementsRequired,const unsigned int &item_number):
	  
						total_bits(item_number),
						total_elements(elementsRequired),
						pool(elementsArray)
		{

		  assert(total_bits);
		  assert(total_elements);
		  assert(pool);

		   int initValue=0;

		  memset(pool,initValue,total_elements * sizeof(T));

		}



    template<typename T>
    Engine::BitPool<T> * Engine::BitPool<T>::CreateBitPool(const unsigned int item_number)
	{
		assert(item_number>0);

		 int elementsRequired=(item_number+ BitPool::bitsPerElement-1)/ BitPool::bitsPerElement;

		assert(elementsRequired>0);

		T *elementsArray= new T[elementsRequired];

		if(elementsArray)
		{
			BitPool *bitpool=new BitPool(elementsArray,elementsRequired,item_number);
			assert(bitpool);
			return bitpool;
		}
		else
    	return NULL;
	}


	 template<typename T>
    void  Engine::BitPool<T>::DestroyBitPool(BitPool *bitpool)
	{
		if(pool)
		{
		  delete pool;
		}

		if(bitpool)
		{
			delete bitpool;
			bitpool=NULL;

			
		}
		
	}


   template<typename T>
   const bool Engine::BitPool<T>::isBitSet(const unsigned int bit) const
   {
		assert(bit>=0);
	  //  assert(bit<total_bits);
	
	   unsigned int checkBit= bit% (sizeof(T) *8);
       unsigned int checkElement=bit/ (sizeof(T) *8);

	   return(pool[checkElement] & (1<< checkBit))!=0;
   }


    template<typename T>
    const bool Engine::BitPool<T>::isBitClear(const unsigned int bit) const
	{
		assert(bit>=0);
	    assert(bit<total_bits);
	
	    return !isBitSet(bit);
	}


    template<typename T>
	void Engine::BitPool<T>::setBit(const unsigned int bit) const
	{

	   assert(bit>=0);
	
	   unsigned int checkBit= bit% (sizeof(T) *8);
       unsigned int checkElement=bit/ (sizeof(T) *8);

	   pool[checkElement] |= (1<< checkBit);
	}


	template<typename T>
	void Engine::BitPool<T>::clearBit(const unsigned int bit)
	{
	   assert(bit>=0);
	   assert(bit<total_bits);
	
	   unsigned int checkBit= bit% (sizeof(T) *8);
       unsigned int checkElement=bit/ (sizeof(T) *8);

	   pool[checkElement] &= ~(1<< checkBit);
	}



     template<typename T>
	 const int Engine::BitPool<T>::nextSetBit()
	  {
			T min=0; //all bits of min set to 0

		unsigned int checkElement=0;
		assert(total_elements>0);

		while(pool[checkElement]==min)
		{
			checkElement++;
		}

		int checkBit=checkElement* (sizeof(T)* 8);

	    while(isBitClear(checkBit) )
			checkBit++;

	unsigned int checkForSpace=( (checkElement)*bitsPerElement ) + checkBit;

		if( checkForSpace>=total_bits)
			return -1;
		else
          return checkBit;
	}


    template<typename T>
    const int Engine::BitPool<T>::nextClearBit()
	{

		T max=~0; //all bits of max set to 1

		unsigned int checkElement=0;
		assert(total_elements>0);
	  

		while(pool[checkElement]==max)
		{
			
			checkElement++;
			
		}

	     int checkBit=checkElement* (sizeof(T)* 8);
	  
	    while(isBitSet(checkBit) )
			checkBit++;
	
		unsigned int checkForSpace=( (checkElement)*bitsPerElement ) + checkBit;

		if( checkForSpace>=total_bits)
			return -1;
		else

			return checkBit;

	}

	