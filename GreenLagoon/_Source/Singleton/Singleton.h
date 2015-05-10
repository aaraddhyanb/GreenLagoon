#ifndef SINGLETON_H
#define SINGLETON_H


namespace Engine
{
	template<class T>
	class Singleton
	{

	    private:

		

		Singleton(){}
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);

		public:

		static T * m_instance;

		static T& getInstance()
		{

			if( m_instance==NULL)
			{
				m_instance= new T;
			}

			return *m_instance;
		}

		static void Shutdown()
		{
			delete m_instance;
			m_instance=NULL;
		}


	};

}

#endif
