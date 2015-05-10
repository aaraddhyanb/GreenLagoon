#include "Clock.h"

namespace Engine
{

void Clock::init()
{
	s_cyclesPerSecond = (float)ReadHiResTimerFrequency();
}

Clock::Clock(float startTimeSeconds):  
	m_timeCycles( secondsToCycles(startTimeSeconds)),  
	m_timeScale( 1.0f), // default to unscaled  
	m_isPaused( false) // default to running
{

}

unsigned long long Clock::getTimeCycles() const
{
	return m_timeCycles;
}

float Clock::calcDeltaSeconds(const Clock& other) 
{  
	unsigned long long  dt = m_timeCycles - other.m_timeCycles;  
	return cyclesToSeconds(dt); 
}

void Clock::Update(float dtRealSeconds) 
{  
	if (!m_isPaused)
	{      
		unsigned long long dtScaledCycles = secondsToCycles(dtRealSeconds * m_timeScale);   
		m_timeCycles += dtScaledCycles; 
		m_deltaCycles = dtScaledCycles;
	}
	else
		m_deltaCycles = 0;
}

void Clock::setPaused(bool isPaused) 
{  
	m_isPaused = isPaused; 
}

bool Clock::isPaused() const 
{  
	return m_isPaused; 
}

void Clock::setTimeScale(float scale) 
{  
	m_timeScale = scale; 
}

float Clock::getTimeScale() const 
{  
	return m_timeScale; 
}

float Clock::getDeltaTime() const
{
	return cyclesToSeconds(m_deltaCycles);
}
void Clock::singleStep() 
{  
	if (m_isPaused)  
	{
		unsigned long long dtScaledCycles = secondsToCycles(( 1.0f/30.0f) * m_timeScale);
		m_timeCycles += dtScaledCycles;  
	} 
}

} 