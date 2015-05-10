#ifndef PLAYERTRIGGER_H
#define PLAYERTRIGGER_H

#include"TriggerBoxController.h"
#include"Actor.h"
#include<cstdlib>

class BoundingBox;
class Actor;

class PlayerTrigger: public Engine::TriggerBoxController
{
private:

public:
	 static int playerScore;
     static bool playerHasFlag;
	 static bool playerTaggedMonster;
	 
     PlayerTrigger(void);
	 virtual void OnCollision(Engine::Actor &i_actor, Engine::Actor &withactor);
};


#endif

