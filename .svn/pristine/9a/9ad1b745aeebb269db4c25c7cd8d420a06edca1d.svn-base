#include"Time.h"

namespace Engine
{

void Time::Init()
{
	GameTime = new Clock();
	Clock::init();
	beginCycle = Clock::GetCurrentCycleTime();
	deltaTime = 1.0f/30.0f;
	
}

float Time::getPassedTime()
{
	unsigned long long temp;
	temp = GameTime->getTimeCycles();
	return GameTime->cyclesToSeconds(temp);
}


void Time::Update()
{
	endCycle = Clock::GetCurrentCycleTime();
	deltaTime = Clock::cyclesToSeconds(endCycle - beginCycle);
	if (deltaTime > 1.0f/10.0f) 
	{  
		deltaTime = 1.0f/30.0f; 
	}
	GameTime->Update(deltaTime);
	deltaTime = GameTime->getDeltaTime();
	beginCycle = endCycle;
	
}

void Time::Shutdown()
{
	delete GameTime;
	GameTime = 0;
	endCycle = 0;
	beginCycle = 0;
	
}


}