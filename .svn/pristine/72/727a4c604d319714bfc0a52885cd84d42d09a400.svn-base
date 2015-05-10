#include"Collision.h"

namespace Engine{

void Collision::Init()
{
	m_SharedPtr.clear();
}


void Collision::AddActor(SharedPointer<Actor> &i_instance)
{
	SharedPointer<Actor> *sharedPtr= new SharedPointer<Actor>(i_instance);
	m_SharedPtr.push_back(sharedPtr);

}

void Collision::RemoveActor(Actor &i_instance)
{
	unsigned int id=i_instance.getID();

   for(unsigned int i=0; i<m_SharedPtr.size(); i++)
	{
		if(id== (*m_SharedPtr[i])->getID() )
		{
			 delete m_SharedPtr[i];
			for(unsigned int j=i; j< m_SharedPtr.size()-1; j++)
			{
			     m_SharedPtr.at(j)=m_SharedPtr.at(j+1);
			}
			 m_SharedPtr.pop_back();
		     break;
		}

	}
}



void Collision::Update(float deltaTime)
{
	for(unsigned int i=0; i<m_SharedPtr.size(); ++i)
	{
		for(unsigned int j=0; j<m_SharedPtr.size(); ++j)
	    {
			if(i!=j)
	          BB::CheckForCollision( *(*m_SharedPtr[i]), *(*m_SharedPtr[j]), deltaTime);
		}
	}
}


void Collision::Shutdown()
{
	for(unsigned int i=0; i< m_SharedPtr.size(); i++)
	{
		delete m_SharedPtr[i];
	}
		  
	m_SharedPtr.erase(m_SharedPtr.begin(),m_SharedPtr.end());
}

}