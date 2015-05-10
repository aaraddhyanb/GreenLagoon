#ifndef WORLD_H
#define WORLD_H

#include<vector>
#include"Actor.h"
#include"Singleton.h"
#include"SharedPointer.h"


namespace Engine{

class ActorController;

class World
{

private:

    friend Singleton<class World>;

    std::vector<class SharedPointer<Actor> *> m_sharedPtr;

 
	    //Private constructors 
		World(){}
		World(const World &i_object);
		void operator=(const World &i_object);


public:

		void Init();
	    Actor * AddActor(const Vector3 i_position, ActorController *const controller, std::string mesh, std::string texture, int i_ID);
		Actor * AddActor(Actor *parent, const Vector3 i_position, ActorController *const controller, int key, int i_ID);
		void RemoveActor(Actor &i_actor);
		void Update(float deltaTime);
		void Shutdown();

		static void ProcessMessage(std::string i_message);
		static void AddMessage(std::string i_message);
		void EnablePhysics(Actor &actor);
		void EnableRenderer(Actor &actor);
		void EnableCollision(Actor &actor);
		void EnableEventHandler(std::string i_message,Actor &actor);

		void DisableEventHandler(std::string i_message,Actor &actor);
		void DisablePhysics(Actor &actor);
		void DisableRenderer(Actor &actor);
		void DisableCollision(Actor &actor);
};

}

#endif