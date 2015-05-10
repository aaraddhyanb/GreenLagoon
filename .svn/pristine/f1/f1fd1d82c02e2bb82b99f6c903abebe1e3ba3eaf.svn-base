#include"BB.h"

namespace Engine{

bool  BB::collided=false;

bool BB::CheckForCollision(Actor &i_actorA,Actor &i_actorB, float deltaTime)
{	
	collided=false;

	if(i_actorA.getActorPosition()->getx() > i_actorB.getBox()->GetMin().getx() &&
		i_actorA.getActorPosition()->gety() > i_actorB.getBox()->GetMin().gety() &&
		i_actorA.getActorPosition()->getz() > i_actorB.getBox()->GetMin().getz() &&

		i_actorA.getActorPosition()->getx() < i_actorB.getBox()->GetMax().getx() &&
		i_actorA.getActorPosition()->gety() < i_actorB.getBox()->GetMax().gety() &&
		i_actorA.getActorPosition()->getz() < i_actorB.getBox()->GetMax().getz()  
		)
	{
		collided=true;
	}

	else if(i_actorB.getActorPosition()->getx() > i_actorA.getBox()->GetMin().getx() &&
			i_actorB.getActorPosition()->gety() > i_actorA.getBox()->GetMin().gety() &&
			i_actorB.getActorPosition()->getz() > i_actorA.getBox()->GetMin().getz()  &&

			i_actorB.getActorPosition()->getx() < i_actorA.getBox()->GetMax().getx() &&
			i_actorB.getActorPosition()->gety() < i_actorA.getBox()->GetMax().gety() &&
			i_actorB.getActorPosition()->getz() < i_actorA.getBox()->GetMax().getz()  
	)
	{
		collided=true;
	}
	
	if(collided)
	{
	   i_actorA.getBox()->getTrigger()->OnCollision(i_actorA, i_actorB);
	   //i_actorB.getBox()->getTrigger()->OnCollision(i_actorB, i_actorA);
	}
	return collided;
}

bool BB::isCollided()
{
	return collided;
}

}