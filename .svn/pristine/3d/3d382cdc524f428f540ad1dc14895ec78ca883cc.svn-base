#ifndef _WORLD_CONTROLLER_H
#define _WORLD_CONTROLLER_H

#include"ActorController.h"

class WorldController: public Engine::ActorController
{
	
public:
	  
	Engine::Actor *player;

	WorldController(void);
    WorldController(Engine::Actor &actor);
	virtual ~WorldController(){}
	virtual void OnMessage(std::string i_message,Engine::Actor &i_actor);
	virtual void updateActor(Engine::Actor &actor);

};


#endif

