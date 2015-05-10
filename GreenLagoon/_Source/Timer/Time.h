#ifndef TIME_H
#define TIME_H

#include "Clock.h"
#include "Singleton.h"


namespace Engine
{

class Time
{
	friend Singleton<class Time>;

	unsigned long long endCycle;
	unsigned long long beginCycle;
	Clock* GameTime;
	
public:
	static float deltaTime;
	

	Time() :
	endCycle(0),
	beginCycle(0),
	GameTime(NULL)
	{
	}

	
	static inline float getDeltaTime() {return deltaTime;}
	float getPassedTime();
	void Init();
	void Update();
	void Shutdown();
	

};

} 
#endif