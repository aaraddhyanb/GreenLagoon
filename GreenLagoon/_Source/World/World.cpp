#include"World.h"

namespace Engine{


void World::Init()
{
	m_sharedPtr.clear();
}

Actor * World::AddActor(const Vector3 i_position, ActorController *const controller, std::string i_meshFile, std::string i_textureFile, int i_ID) 
{
	int *ref_count=(int * )malloc(sizeof(int));
	*ref_count=0;

	Actor *o_Actor=Actor::CreateActor(i_position,controller, i_meshFile, i_textureFile, i_ID);
	SharedPointer<Actor> *sharedPtr=new SharedPointer<Actor>(o_Actor, ref_count);
	m_sharedPtr.push_back(sharedPtr);
	return o_Actor;
}

Actor * World::AddActor(Actor *parent, const Vector3 i_position, ActorController *const controller, int key, int i_ID) 
{
	int *ref_count=(int * )malloc(sizeof(int));
	*ref_count=0;

	Actor *o_Actor=Actor::CreateActor(parent, i_position, controller, key, i_ID);
	SharedPointer<Actor> *sharedPtr=new SharedPointer<Actor>(o_Actor, ref_count);
	m_sharedPtr.push_back(sharedPtr);
	return o_Actor;
}

void World::RemoveActor(Engine::Actor &i_actor)
{
    unsigned int id=i_actor.getID();

	for(unsigned int i=0; i<m_sharedPtr.size(); i++)
	{
		if(id== (*m_sharedPtr[i])->getID() )
		{
			 delete m_sharedPtr[i];
			for(unsigned int j=i; j< m_sharedPtr.size()-1; j++)
			{
			     m_sharedPtr.at(j)=m_sharedPtr.at(j+1);
			}
			 m_sharedPtr.pop_back();
		     break;
		}

	}
	DisableCollision(i_actor);
	DisablePhysics(i_actor);
	DisableRenderer(i_actor);

	//searching all the entries in EventHandler and deleting the sharedptr
	Singleton<EventHandler>::getInstance().RemoveAllActors(i_actor);
}


void World::ProcessMessage(std::string i_message)
{
	Singleton<EventHandler>::getInstance().ProcessMessage(i_message);
}


void World::AddMessage(std::string i_message)
{
	Singleton<EventHandler>::getInstance().AddMessage(i_message);
}



void World::Update(float deltaTime)
{
	int number_of_elements=m_sharedPtr.size();

    for(int i=0; i<number_of_elements;i++)
	{

		(*m_sharedPtr[i])->update();
		
	}
	
}



void World::EnableEventHandler(std::string i_message,Actor &actor)
{
	int number_of_elements=m_sharedPtr.size();


	 for(int i=0; i<number_of_elements;i++)
	{

		if( (*m_sharedPtr[i])->getID()== actor.getID() )
		{
			Singleton<EventHandler>::getInstance().AddActor(i_message,*m_sharedPtr[i]);
			break;
		}
		
	}
}
void World::EnablePhysics(Actor &actor)
{
	int number_of_elements=m_sharedPtr.size();


	 for(int i=0; i<number_of_elements;i++)
	{

		if( (*m_sharedPtr[i])->getID()== actor.getID() )
		{
			Singleton<Physics>::getInstance().AddActor(*m_sharedPtr[i]);
			break;
		}
		
	}
	
}


void World::EnableRenderer(Actor &actor)
{
	int number_of_elements=m_sharedPtr.size();


	 for(int i=0; i<number_of_elements;i++)
	{

		if( (*m_sharedPtr[i])->getID()== actor.getID() )
		{
			Singleton<Renderer>::getInstance().AddActor(*m_sharedPtr[i]);
			break;
		}
		
	}
	
}

void World::EnableCollision(Actor &actor)
{
	int number_of_elements=m_sharedPtr.size();


	 for(int i=0; i<number_of_elements;i++)
	{

		if( (*m_sharedPtr[i])->getID()== actor.getID() )
		{
			Singleton<Collision>::getInstance().AddActor(*m_sharedPtr[i]);
			break;
		}
		
	}
	
}

void World::DisableEventHandler(std::string i_message,Actor &actor)
{
	
	Singleton<EventHandler>::getInstance().RemoveActor(i_message,actor);
	
}


void World::DisableCollision(Actor &actor)
{
	
	Singleton<Collision>::getInstance().RemoveActor(actor);
	
}

void World::DisableRenderer(Actor &actor)
{
	
	Singleton<Renderer>::getInstance().RemoveActor(actor);
	
	
}

void World::DisablePhysics(Actor &actor)
{
	Singleton<Physics>::getInstance().RemoveActor(actor);
	
}

void World::Shutdown()
{
	for(unsigned int i=0; i< m_sharedPtr.size(); i++)
	{
		delete m_sharedPtr[i];
	}
			
		  
	m_sharedPtr.erase(m_sharedPtr.begin(),m_sharedPtr.end());
	
}

} //namespace end