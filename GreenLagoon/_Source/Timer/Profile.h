#ifndef PROFILE_H
#define PROFILE_H

#include<Windows.h>


namespace Engine
{
	

class Profile
{
	long long m_start;
	long long m_end;
	bool timerRunning;
	
  public:
	
	void StartTick();
	void StopTick();
	float DifferenceInTick();
	

};

} 
#endif