#ifndef _ACTOR_CONTROLLER_H
#define _ACTOR_CONTROLLER_H

#include"Actor.h"
#include<string>

using namespace std;

namespace Engine
{
	class Actor;


class ActorController
{

public:

    ActorController(void){};
	virtual ~ActorController(void){};
	virtual void updateActor(Actor & actor)=0;
	virtual void OnMessage(std::string i_message,Engine::Actor &actor)=0;


};

}//namespace end

#endif

