#ifndef PHYSICS_H
#define PHYSICS_H

#include<vector>
#include"Actor.h"
#include"Singleton.h"
#include"SharedPointer.h"

namespace Engine
{
	class Actor;

    class Physics 
    { 

      private:

		friend Singleton<class Physics>;
		std::vector<class SharedPointer<Actor> *> m_SharedPtr;
		//Vector3 m_velocity;
		//Vector3 m_acceleration;
		//Vector3 m_position;

	
	
		//Private constructors 
		Physics(){}
		Physics(const Physics &i_object);
		void operator=(const Physics &i_object);
	
	  public:


		void Init();
		void AddActor(SharedPointer<Actor> &i_instance);
		void RemoveActor(Actor &i_instance);
		void Update(float deltaTime);
		void Shutdown();
   };

}
#endif