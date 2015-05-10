#ifndef RINGBUFFER_H
#define RINGBUFFER_H

namespace Engine
{


template<typename T, unsigned int S>
class RingBuffer
{
	private:
	T data[S+1];            //size +1 for index manipulation
	unsigned int r_count;
	unsigned int ring_first;   //always points at 0 idex
	unsigned int ring_current; // points at index where new value is to be stored
	unsigned int ring_last;    //always points at the ring_count that is last 

	public:

    RingBuffer(void);
	
	void push(const T  &i_value);

	//pops and deletes the last entered value of type T
	const T& pop();

	//returns the value of type T at location=index
	const T& getAt(unsigned int index) const;


	//returns the index of the last element
    unsigned int numberOfElements();


};


}


#include"RingBuffer.inl"

#endif