#include"PlayerTrigger.h"
#include"..\Code\Renderer\cRenderer.h"
#include"SoundManager.h"
#include"MonsterTrigger.h"

using namespace Engine;

int PlayerTrigger::playerScore=0;
bool PlayerTrigger::playerHasFlag=false;
bool PlayerTrigger::playerTaggedMonster=false;

//Zero argument constructor
PlayerTrigger::PlayerTrigger(void)
{
	
}

void PlayerTrigger::OnCollision(Engine::Actor &i_actor, Engine::Actor &withActor)
{
	if( (i_actor.getID()==1 && withActor.getID()==1001) ||
		(i_actor.getID()==1001 && withActor.getID()==1) )
	{
		playerTaggedMonster=true;
		if(playerHasFlag || MonsterTrigger::monsterHasFlag)
			SoundManager::Manager().PlayOneShot("reset.wav");
	}
	
	if(i_actor.getID()==1 && withActor.getID()==4) //Monser is 1 and flag is 4
	{
		if(!playerHasFlag)
			SoundManager::Manager().PlayOneShot("playerPickedFlag.wav");

		playerHasFlag=true;
        withActor.setActorPosition(*i_actor.getActorPosition());

		//tagged reset flag position
		if(playerTaggedMonster)
		{
			withActor.setActorPosition(*withActor.getActorPreviousPosition());
		    playerTaggedMonster=false;
			playerHasFlag=false;
		}
	}
	if(i_actor.getID()==4 && withActor.getID()==1) //player is 1 and flag is 4
	{
		i_actor.setActorPosition(*withActor.getActorPosition());

		//tagged reset flag position
		if(playerTaggedMonster)
		{
			i_actor.setActorPosition(*i_actor.getActorPreviousPosition());
			playerTaggedMonster=false;
			playerHasFlag=false;
		}
	}	

	if(i_actor.getID()==4 && withActor.getID()==102)
	{
		SoundManager::Manager().PlayOneShot("playerScored.wav");
		i_actor.setActorPosition(*i_actor.getActorPreviousPosition());
		playerScore++;
		playerHasFlag=false;
	}
}

