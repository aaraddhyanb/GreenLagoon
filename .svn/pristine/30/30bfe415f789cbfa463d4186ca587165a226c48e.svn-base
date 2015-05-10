#include"Physics.h"

namespace Engine{

	

void Physics::Init()
{
	m_SharedPtr.clear();
}


void Physics::AddActor(SharedPointer<Actor> &i_instance)
{
	SharedPointer<Actor> *sharedPtr= new SharedPointer<Actor>(i_instance);
	m_SharedPtr.push_back(sharedPtr);

}

void Physics::RemoveActor(Actor &i_instance)
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


void Physics::Update(float deltaTime)
{


    for(unsigned int i=0; i<m_SharedPtr.size();i++)
	{
		
		Vector3 t_position=*(*m_SharedPtr[i])->getActorPosition();
		Vector3 t_velocity=*(*m_SharedPtr[i])->getActorVelocity();
		Vector3 t_acceleration=*(*m_SharedPtr[i])->getActorAcceleration();

		//Euler Intergration
		t_velocity = t_velocity + t_acceleration * deltaTime;
		t_position = t_position + t_velocity * deltaTime;
	     
		(*m_SharedPtr[i])->setActorPosition(t_position);
		(*m_SharedPtr[i])->setActorVelocity(t_velocity);

	}
	
}


void Physics::Shutdown()
{
			
	for(unsigned int i=0; i< m_SharedPtr.size(); i++)
	{
		delete m_SharedPtr[i];
	}
			
		  
	m_SharedPtr.erase(m_SharedPtr.begin(),m_SharedPtr.end());
	
}

} //namespace end