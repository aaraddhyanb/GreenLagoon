#include"JumpTrigger.h"
#include"..\Code\Renderer\cRenderer.h"

using namespace Engine;

//Zero argument constructor
JumpTrigger::JumpTrigger(void)
{
	
}

void JumpTrigger::OnCollision(Engine::Actor &i_actor, Engine::Actor &withActor)
{
	Engine::Vector3 position;
	position.setx(withActor.getActorPosition()->getx());
	position.sety(withActor.getActorPosition()->gety()+20.0f);
	position.setz(withActor.getActorPosition()->getz());
	withActor.setActorPosition(position);
}

