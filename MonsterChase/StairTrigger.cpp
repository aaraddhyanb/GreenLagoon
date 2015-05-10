#include"StairTrigger.h"
#include"PlayerController.h"
//#include"..\Code\Renderer\cRenderer.h"
#include"SoundManager.h"

using namespace Engine;

//Zero argument constructor
StairTrigger::StairTrigger(void)
{
	
}

void StairTrigger::OnCollision(Engine::Actor &i_actor, Engine::Actor &withActor)
{
	if( (i_actor.getID()==4000)  && (withActor.getID()==1) )
	{
		PlayerController::playerHardSurfaceChannel->setPaused(false);
	}
}

