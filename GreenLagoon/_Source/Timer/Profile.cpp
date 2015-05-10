#include"Profile.h"

namespace Engine
{
	
void Profile::StartTick()
{
	timerRunning=true;
    LARGE_INTEGER Counter;
	QueryPerformanceCounter( &Counter );
	m_start=Counter.QuadPart;
}


void Profile::StopTick()
{
	if(timerRunning)
	{
		LARGE_INTEGER Counter;
		QueryPerformanceCounter( &Counter );
		m_end=Counter.QuadPart;
		timerRunning=false;
	}
	
}

float Profile::DifferenceInTick()
{
	LARGE_INTEGER Counter;
	LARGE_INTEGER PerformanceFrequency;
	QueryPerformanceCounter( &Counter );
	QueryPerformanceFrequency(&PerformanceFrequency);
	double difference=static_cast<double>(( (m_end-m_start) *1000 )/ (double)PerformanceFrequency.QuadPart);
	return static_cast<float>(difference);
}


}