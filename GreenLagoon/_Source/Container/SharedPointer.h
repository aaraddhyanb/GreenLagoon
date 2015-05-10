#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

namespace Engine
{
	template<typename T>
	class SharedPointer
	{
	
	private:

		T  * m_ref_pointer;
		int * m_ref_count;

	
		SharedPointer(){}

   	public:

			
		 
		SharedPointer(T * i_instance, int * i_ref_count)
		{
			m_ref_pointer=i_instance;
			m_ref_count=i_ref_count;
			(*m_ref_count)++;

		}

		SharedPointer(SharedPointer & pointer)
		{
			*this=pointer;
			(*m_ref_count)++;
		}

		
	    T & operator*() 
		{
			assert( m_ref_pointer );
		
			return *m_ref_pointer;
		}
	
	    T * operator->()
		{
			return m_ref_pointer;
		}

		~SharedPointer()
		{
			release();
		}

	private:

		void release()
			{
				assert( m_ref_count );
				assert( *m_ref_count > 0 );
		
				if( --(*m_ref_count) == 0 )
				{
					free( m_ref_count );

					m_ref_count = 0;
			
					if( m_ref_pointer )
						delete m_ref_pointer;

					m_ref_pointer = 0;
				}
			}
	};

}
#endif