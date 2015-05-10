#include"MonsterTrigger.h"
#include"..\Code\Renderer\cRenderer.h"


using namespace Engine;

int MonsterTrigger::monsterScore=0;
bool MonsterTrigger::monsterHasFlag=false;
bool MonsterTrigger::monsterTaggedPlayer=false;
FMOD::Channel *MonsterTrigger::monsterChannel;

//Zero argument constructor
MonsterTrigger::MonsterTrigger(void)
{
}

void MonsterTrigger::SetChannel(std::string soundName,Engine::Actor *monster, Engine::Actor *player)
{
	monsterChannel= SoundManager::Manager().PlayLoop3D(soundName, monster->getActorPosition(), player->getActorPosition());
}

void MonsterTrigger::OnCollision(Engine::Actor &i_actor, Engine::Actor &withActor)
{
	if( (i_actor.getID()==1 && withActor.getID()==1001) ||
		(i_actor.getID()==1001 && withActor.getID()==1) )
	{
		monsterTaggedPlayer=true;
	}
	
	if(i_actor.getID()==1001 && withActor.getID()==5) //Monser is 1001 and flag is 5
	{
		if(!monsterHasFlag)
			SoundManager::Manager().PlayOneShot("monsterPickedFlag.wav");

		monsterHasFlag=true;
        withActor.setActorPosition(*i_actor.getActorPosition());

		//tagged reset flag position
		if(monsterTaggedPlayer)
		{
			SoundManager::Manager().PlayOneShot("reset.wav");
			withActor.setActorPosition(*withActor.getActorPreviousPosition());
			monsterTaggedPlayer=false;
			monsterHasFlag=false;
		}
	}
	else if(i_actor.getID()==5 && withActor.getID()==1001) //Monser is 1001 and flag is 5
	{
		//monsterHasFlag=true;

		//tagged reset flag position
		if(monsterTaggedPlayer)
		{
			SoundManager::Manager().PlayOneShot("reset.wav");
			i_actor.setActorPosition(*i_actor.getActorPreviousPosition());
			monsterTaggedPlayer=false;
			monsterHasFlag=false;
		}
	}	
	
	if(i_actor.getID()==5 && withActor.getID()==101)
	{
		SoundManager::Manager().PlayOneShot("monsterScored.wav");
		i_actor.setActorPosition(*i_actor.getActorPreviousPosition());
		monsterHasFlag=false;
		monsterScore++;
	}
}

