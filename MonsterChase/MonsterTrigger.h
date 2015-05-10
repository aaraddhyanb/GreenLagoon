#ifndef MONSTERTRIGGER_H
#define MONSTERTRIGGER_H

#include"TriggerBoxController.h"
#include"Actor.h"
#include<cstdlib>

#include"SoundManager.h"

class BoundingBox;
class Actor;

class MonsterTrigger: public Engine::TriggerBoxController
{
private:

public:
	 static int monsterScore;
     static bool monsterHasFlag;
	 static bool monsterTaggedPlayer;
	 static FMOD::Channel *monsterChannel;
	 static void SetChannel(std::string soundName, Engine::Actor *monster, Engine::Actor *player);

     MonsterTrigger(void);
	 virtual void OnCollision(Engine::Actor &i_actor, Engine::Actor &withactor);
};


#endif

