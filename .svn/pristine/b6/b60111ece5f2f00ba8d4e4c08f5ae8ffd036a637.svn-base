#ifndef COLLISION_H
#define COLLISION_H

#include"Actor.h"
#include<vector>
#include"Singleton.h"
#include"SharedPointer.h"
#include"AABB.h"
#include"BB.h"

namespace Engine
{
	class Actor;

	class Collision
	{

	private:

		std::vector<class SharedPointer<Actor> *> m_SharedPtr;

		friend Singleton<class Collision>;
		//Private constructors 
		Collision(){}
		Collision(const Collision &i_object);
		void operator=(const Collision &i_object);
	
	  public:

		void Init();
		void AddActor(SharedPointer<Actor> &i_instance);
		void RemoveActor(Actor &i_instance);
		void Update(float deltaTime);
		void Shutdown();



	};

}
#endif