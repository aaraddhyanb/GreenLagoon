#include"EventHandler.h"

namespace Engine{

	

void EventHandler::Init()
{
	m_messages.clear();
	m_SubscribedActors.clear();
	m_SubscribedActors.resize(5);
	//for(unsigned int i=0;i<5;i++)
	//	m_SubscribedActors.at(i).resize(5);
}


void EventHandler::AddMessage(std::string i_message)
{
	m_messages.push_back(i_message);

}


void EventHandler::RemoveMessage(std::string i_message)
{
	for(unsigned int i=0; i<m_messages.size(); i++)
	{
		if(i_message.compare(m_messages.at(i) )==0 )
		{
			for(unsigned int j=i; j< m_messages.size()-1; j++)
			{
				//Shifting the messages up to pop out the last message
				m_SubscribedActors.at(j)=m_SubscribedActors.at(j+1);

				//Shifting the corresponding actors list to pop out last list
			    m_messages.at(j)=m_messages.at(j+1);
			}
			m_messages.pop_back();
			m_SubscribedActors.pop_back();
		    break;
		}
	}
}


void EventHandler::RemoveAllActors(Actor &i_actor)
{
	 unsigned int id=i_actor.getID();

	for(unsigned int i=0;i<m_SubscribedActors.size();i++)
	{
		    
			 for(unsigned int j=0; j<m_SubscribedActors.at(i).size(); j++)
			  {
					if(id== (*m_SubscribedActors[i].at(j))->getID() )
					{
						delete m_SubscribedActors[i].at(j);
						
						for(unsigned int k=j; k< m_SubscribedActors.at(i).size()-1; k++)
						{
							 m_SubscribedActors[i].at(k)= m_SubscribedActors[i].at(k+1);
						}
			
			              m_SubscribedActors[i].pop_back();
						  break;

					}
		      }
	}

}

 


void EventHandler::AddActor(std::string i_message,SharedPointer<Actor> &i_instance)
{
	SharedPointer<Actor> *sharedPtr= new SharedPointer<Actor>(i_instance);

	for(unsigned int i=0; i<m_messages.size();i++)
	{
		if(i_message.compare(m_messages.at(i) )==0)
		{
			
     		m_SubscribedActors.at(i).push_back(sharedPtr);
		}
		break;
	}

}

void EventHandler::RemoveActor(std::string i_message,Actor &i_actor)
{
	for(unsigned int i=0; i<m_messages.size(); i++)
	{
		if(i_message.compare(m_messages.at(i) )==0 )
		{
			 unsigned int id=i_actor.getID();

			 for(unsigned int j=0; j<m_SubscribedActors.at(i).size(); j++)
				{
					if(id== (*m_SubscribedActors[i].at(j))->getID() )
					{
						 delete m_SubscribedActors[i].at(j);
						for(unsigned int k=j; k< m_SubscribedActors.at(i).size()-1; k++)
						{
							 m_SubscribedActors[i].at(k)= m_SubscribedActors[i].at(k+1);
						}
			
			              m_SubscribedActors[i].pop_back();
						  break;
					 }
			    
			}
		    break;
		}
	}

}


void EventHandler::ProcessMessage(std::string i_message)
{
	//searching for message in vector list
	for(unsigned int i=0; i<m_messages.size(); i++)
	{
		if(i_message.compare(m_messages.at(i) )==0 )
		{
			for(unsigned int j=0; j<m_SubscribedActors.at(i).size(); j++)
			{
				(*m_SubscribedActors.at(i).at(j))->sendMessage(i_message);			
			}
			break;
		}
	}

	
}



void EventHandler::Shutdown()
{
			
	for(unsigned int i=0;i<m_SubscribedActors.size();i++)
	{
		for(unsigned int j=0; j< m_SubscribedActors.at(i).size(); j++)
		{
			delete m_SubscribedActors[i].at(j);
		}
	}
			
		  
	m_messages.erase(m_messages.begin(),m_messages.end());
	for(unsigned int i=0;i<m_SubscribedActors.size();i++)
		m_SubscribedActors[i].erase(m_SubscribedActors[i].begin(),m_SubscribedActors[i].end() );

	m_SubscribedActors.erase(m_SubscribedActors.begin(), m_SubscribedActors.end() );
}

} //namespace end