//#include"Util.h"
//#include<assert.h>


   template<typename T, unsigned int S>
    Engine::RingBuffer<T,S>::RingBuffer(void)
	{
	   r_count=S;
	   
	   ring_first=0;
	   ring_current=ring_first;
	   ring_last=r_count;
	}

	
    template<typename T, unsigned int S>
	void  Engine::RingBuffer<T,S>::push(const T  &i_value)
	{
		
		assert(ring_current>=ring_first);
		assert(ring_current<=ring_last);
	

	    //pushing the value at index=ring_current
		data[ring_current]=i_value;
		
		if(ring_current!=ring_last) 
			ring_current++;
		else
		{
			ring_current=ring_first;
			
			assert(ring_current==ring_first);

			//moving all the values up in the array by 1 
			//and throwing the top most element.
			while(ring_current!=ring_last)
			{ 

				data[ring_current]= data[ring_current+1];
				ring_current++;

		    }
		  
			
		}
		assert(ring_first==0);
	}



	//pops and deletes the last entered value of type T
	template<typename T, unsigned int S>
	const T& Engine::RingBuffer<T,S>::pop()
	{
		
		assert(ring_current>=ring_first);
		assert(ring_current<=ring_last);
	
		T temp=data[ring_current];
		//printf("\nPopped out %d out of buffer",temp);
		ring_current--;

		assert(temp!=NULL);
		return temp;

	}




	//returns the value of type T at location=index
    template<typename T, unsigned int S>
	const T& Engine::RingBuffer<T,S>::getAt(unsigned int index) const
	{
		
		assert(index>=ring_first);
		assert(index<=ring_last);
	
		return(data[index]); 

	}

	//returns the index of the last element
    template<typename T, unsigned int S>
    unsigned int Engine::RingBuffer<T,S>::numberOfElements() 
	{
		assert(ring_current>=ring_first);
		return (ring_current-1);

	}

