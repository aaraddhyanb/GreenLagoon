#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include<vector>
#include"Actor.h"
#include"Singleton.h"
#include"SharedPointer.h"

namespace Engine
{
	class Actor;

    class EventHandler 
    { 

      private:

		friend Singleton<class EventHandler>;  

		std::vector<std::string> m_messages;
		std::vector<vector<class SharedPointer<Actor> *>> m_SubscribedActors;
		
		//Private constructors 
		EventHandler(){}
		EventHandler(const EventHandler &i_object);
		void operator=(const EventHandler &i_object);
	

	  public:

		void Init();
		void AddMessage(std::string i_message);
		void RemoveMessage(std::string i_message);
		void AddActor(std::string i_message,SharedPointer<Actor> &i_instance);
		void RemoveActor(std::string i_message,Actor &i_actor);
		void RemoveAllActors(Actor &i_actor);
		void ProcessMessage(std::string i_message);
		void Shutdown();
   };

}
#endif