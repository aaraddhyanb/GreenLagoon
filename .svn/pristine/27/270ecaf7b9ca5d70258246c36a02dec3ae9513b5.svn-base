#ifndef _SMARTAI_CONTROLLER_H
#define _SMARTAI_CONTROLLER_H

#include"ActorController.h"

enum MonsterStates
{
	isChasing=1,
	isEvading,
	isGoingForFlag,
	isGoingHome,
};

class SmartAIController: public Engine::ActorController
{
private:
	 MonsterStates monsterIs;
	 D3DXVECTOR3 currentGoal;
	 Engine::Vector3 evadePoints[5];

public:
	  
	Engine::Vector3 flagPosition;
	Engine::Vector3 homePosition;

	Engine::Actor *player;
	std::vector<D3DXVECTOR3> positionToFollow;

	float DistanceXZ(Engine::Vector3 A, Engine::Vector3 B);
	float DistanceXYZ(Engine::Vector3 A, Engine::Vector3 B);

	float speed;
	bool useSprint;

	static float getScore();
	static float getStamina();

	static float monsterStamina;

	SmartAIController(void);
    SmartAIController(Engine::Actor &actor);
    void PathFind(Engine::Actor & actor, D3DXVECTOR3 newGoal);
	void CheckState(Engine::Actor & actor);

	virtual ~SmartAIController(){}
	virtual void OnMessage(std::string i_message,Engine::Actor &i_actor);
	virtual void updateActor(Engine::Actor &actor);
};

#endif

