#include"SmartAIController.h"
#include"MonsterTrigger.h"
#include"PlayerTrigger.h"
#include"_Source\AI\WaypointsData.h"
#include"_Source\AI\PathFinding.h"
#include"..\Code\Renderer\TextField.h"
#include"..\Code\Renderer\cRenderer.h"

float SmartAIController::monsterStamina=10;

#define PI 3.14159265


using namespace Engine;

//zero arg construct
SmartAIController::SmartAIController(void)
{
	TextField *score;
	score=new TextField();
	cs6963::cMainWindow::GetSingleton().m_renderer.AddText(score, "Monster:", 1100, 700, &getScore);

	TextField *stamina;
	stamina=new TextField();
	cs6963::cMainWindow::GetSingleton().m_renderer.AddText(stamina, "Stamina:", 1100, 750, &getStamina);

	evadePoints[0]= Engine::Vector3(-17.58f, -207, 1390);
	evadePoints[1]= Engine::Vector3(49, 91.79f, -27);
	evadePoints[2]= Engine::Vector3(-669, 92.47f, -782.86f);
	evadePoints[3]= Engine::Vector3(1351.66f, -207.53f, -335.8f);
	evadePoints[4]= Engine::Vector3(-29.2f, -207.53f, -1423.68f);

	monsterIs=MonsterStates::isGoingForFlag;

	speed=1.0f;
	useSprint=false;
}

float SmartAIController::getScore()
{
	return MonsterTrigger::monsterScore;
}

float SmartAIController::getStamina()
{
	return SmartAIController::monsterStamina;
}

SmartAIController::SmartAIController(Engine::Actor & actor)
{
	player=&actor;
}


void SmartAIController::OnMessage(std::string i_message, Engine::Actor &i_actor)
{
}

float SmartAIController::DistanceXZ(Engine::Vector3 A, Engine::Vector3 B)
{
	float distance= (B.getx() -A.getx()) * (B.getx() -A.getx()) +
					(B.getz() -A.getz()) * (B.getz() -A.getz());
	distance = sqrt(distance);
	return distance;
}

float SmartAIController::DistanceXYZ(Engine::Vector3 A, Engine::Vector3 B)
{
	float distance= (B.getx() -A.getx()) * (B.getx() -A.getx()) +
					(B.gety() -A.gety()) * (B.gety() -A.gety()) +
					(B.getz() -A.getz()) * (B.getz() -A.getz());
	distance = sqrt(distance);
	return distance;
}

void SmartAIController::updateActor(Engine::Actor & actor)
{
	if(SmartAIController::monsterStamina<10.0f)
		SmartAIController::monsterStamina+=0.05f;


	//collision
	actor.DetectCollision();

	//FSM
	CheckState(actor);
}

void SmartAIController::CheckState(Engine::Actor & actor)
{
	bool playerIsInRadius=false;
	float distance=DistanceXYZ(*player->getActorPosition(), *actor.getActorPosition());
	if(distance<=400.0f)
	{
		playerIsInRadius=true;
	}

	if(monsterIs==MonsterStates::isGoingForFlag)
	{
		if(playerIsInRadius && PlayerTrigger::playerHasFlag)
		{
			monsterIs=MonsterStates::isChasing;
		}
		else if(MonsterTrigger::monsterHasFlag)
		{
			monsterIs=MonsterStates::isGoingHome;
		}
	}
	else if(monsterIs==MonsterStates::isGoingHome)
	{
		if(playerIsInRadius && !PlayerTrigger::playerHasFlag)
		{
			monsterIs=MonsterStates::isEvading;
		}
		else if(playerIsInRadius && PlayerTrigger::playerHasFlag)
		{
			monsterIs=MonsterStates::isEvading;
		}
		
		if(!MonsterTrigger::monsterHasFlag)
		{
			monsterIs=MonsterStates::isGoingForFlag;
		}
	}
	else if(monsterIs==MonsterStates::isChasing)
	{
		//chase
		//D3DXVECTOR3 playerPosition= D3DXVECTOR3( player->getActorPosition()->getx(),
													//player->getActorPosition()->gety(),
													//player->getActorPosition()->getz());
		//PathFind(actor, playerPosition);

		Vector3 follow;
		follow.setx(player->getActorPosition()->getx() - actor.getActorPosition()->getx());
		follow.sety(player->getActorPosition()->gety() - actor.getActorPosition()->gety());
		follow.setz(player->getActorPosition()->getz() - actor.getActorPosition()->getz());
	
		follow=follow.Normalize();

		D3DXVECTOR3 newFollow;
		newFollow= D3DXVECTOR3(follow.getx()* 40, 0, follow.getz()* 40);

		actor.TransLatePosition(newFollow);

		if(!playerIsInRadius)
		{
			monsterIs=MonsterStates::isGoingForFlag;
		}

		if(MonsterTrigger::monsterTaggedPlayer)
		{
			monsterIs=MonsterStates::isGoingForFlag;
		}
	}
	else if(monsterIs==MonsterStates::isEvading)
	{
		Engine::Vector3 distance= Engine::Vector3( (player->getActorPosition()->getx() - actor.getActorPosition()->getx()),
													 (player->getActorPosition()->gety() - actor.getActorPosition()->gety()),
													  (player->getActorPosition()->getz() - actor.getActorPosition()->getz()));
			
		Engine::Vector3 direction= distance.Normalize();

		int choosenEvadePointIndex=-1;
		for(int i=0; i<5; ++i)
		{
				Engine::Vector3 evadePointDistance= Engine::Vector3( (evadePoints[i].getx() - actor.getActorPosition()->getx()),
												    	 (evadePoints[i].gety() - actor.getActorPosition()->gety()),
													   (evadePoints[i].getz() - actor.getActorPosition()->getz()));
		
			Engine::Vector3 evadePointDirection= evadePointDistance.Normalize();

			float dotProduct= evadePointDirection.getx()* direction.getx() +
				                 evadePointDirection.gety()* direction.gety() +
	                             evadePointDirection.getz()* direction.getz();

			float angle=acos(dotProduct) * 180.0 / PI;

			if(angle<270.0f && angle>90.0f)
			{
				choosenEvadePointIndex=i;
				break;
			}
		}

		D3DXVECTOR3 evadePosition= D3DXVECTOR3( evadePoints[choosenEvadePointIndex].getx(),
													evadePoints[choosenEvadePointIndex].gety(),
													evadePoints[choosenEvadePointIndex].getz());
		//evade
		PathFind(actor, evadePosition);
		
		if(!playerIsInRadius)
		{
			monsterIs=MonsterStates::isGoingHome;
		}

		if(MonsterTrigger::monsterTaggedPlayer)
		{
			monsterIs=MonsterStates::isGoingForFlag;
		}
	}

	if(monsterIs==MonsterStates::isGoingHome)
	{
		D3DXVECTOR3 goal = D3DXVECTOR3( homePosition.getx(), homePosition.gety(), homePosition.getz());
		PathFind(actor, goal);
	}
	else if(monsterIs==MonsterStates::isGoingForFlag)
	{
		D3DXVECTOR3 goal = D3DXVECTOR3( flagPosition.getx(), flagPosition.gety(), flagPosition.getz());
		PathFind(actor, goal);
	}

	if(monsterIs==MonsterStates::isChasing || monsterIs==MonsterStates::isEvading)
	{
		useSprint=true;
	}

	if(monsterStamina<2.0f)
	{
		speed=1.0f;
		useSprint=false;
	}

	if(useSprint)
	{
		speed=1.8f;
		monsterStamina-=0.2f;
		useSprint=true;
	}
}


void SmartAIController::PathFind(Engine::Actor & actor, D3DXVECTOR3 newGoal)
{
	Engine::Vector3 nGoal= Engine::Vector3(newGoal.x, newGoal.y, newGoal.z);
	Engine::Vector3 cGoal= Engine::Vector3(currentGoal.x, currentGoal.y, currentGoal.z);
	
	if(positionToFollow.size()<=0 || (DistanceXYZ(nGoal, cGoal)>20.0f))
	{
		if( (DistanceXYZ(nGoal, cGoal)>20.0f))
			currentGoal=newGoal;

		//AI
		PathFinding playerPath;
		playerPath.SetLinks(Engine::WaypointsData::Manager().links);
		playerPath.SetPoints(Engine::WaypointsData::Manager().points);
		D3DXVECTOR3 currentPos= D3DXVECTOR3( actor.getActorPosition()->getx(), actor.getActorPosition()->gety(), actor.getActorPosition()->getz() );

		positionToFollow=playerPath.findShortestPathByAstar(currentGoal,currentPos);
	}

	Engine::Vector3 closestPositionToFollow= Vector3(positionToFollow[0].x,  positionToFollow[0].y,  positionToFollow[0].z);
	
	float distance=DistanceXZ(closestPositionToFollow, *actor.getActorPosition());

	if(distance<30.0f)
	{
		positionToFollow.erase(positionToFollow.begin() + 0);
	}
	else
	{
		Vector3 follow;
		follow.setx(positionToFollow[0].x - actor.getActorPosition()->getx());
		follow.sety(positionToFollow[0].y - actor.getActorPosition()->gety());
		follow.setz(positionToFollow[0].z - actor.getActorPosition()->getz());
	
		follow=follow.Normalize();

		D3DXVECTOR3 newFollow;
		newFollow= D3DXVECTOR3(follow.getx()* 20 *speed, 0, follow.getz()* 20 *speed);

		actor.TransLatePosition(newFollow);
	}
}