
#include "Vector3.h"

using namespace Engine;

MemoryPool * myMemoryPool=NULL;

void * Engine::Vector3::operator new(unsigned int size)
{

	if(myMemoryPool==NULL)
		{
			myMemoryPool=Engine::MemoryPool::CreateMemoryPool(sizeof(Engine::Vector3),100);
			printf("\nMemory pool of 100 Vector3 created");
	    }

	assert(myMemoryPool);

	//searching for next free bit 
	 return myMemoryPool->alloc(1);

}
 



void Engine::Vector3::operator delete(void *ptr)
{
	//calculating bit number
	unsigned int bit=((int)ptr-(int)myMemoryPool)/sizeof(Engine::Vector3);

	//setting bit to 0;
	myMemoryPool->freeSpace(bit);


}



float Engine::Vector3::Length()
{
	float o_value=  pow(x,2) +pow(y,2)+pow(z,2);
    return sqrt(o_value);
}


Engine::Vector3 Engine::Vector3::Normalize()
{
    float length= Length();

	if (length==0)
		return Vector3(length,length,length);

	float temp =x/length;
	float tempy=y/length;
	return Vector3(x/length,y/length,z/length);
}
