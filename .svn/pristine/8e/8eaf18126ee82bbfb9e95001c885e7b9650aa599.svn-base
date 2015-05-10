#ifndef CLOCK_H
#define CLOCK_H


#include <Windows.h>

namespace Engine
{

class Clock
{
	unsigned long long m_timeCycles;
	unsigned long long m_deltaCycles;
	float m_timeScale;
	bool m_isPaused;
	

		static inline unsigned long long secondsToCycles(float timeSeconds);
		
		static inline float ReadHiResTimerFrequency();
		

	public:
		static float s_cyclesPerSecond;

		static inline float cyclesToSeconds(unsigned long long timeCycles); //Only use to convert small durations unsigned into seconds. 
		static inline unsigned long long GetCurrentCycleTime();

		static void init();		// Call this when the game first starts up.

		explicit Clock(float startTimeSeconds = 0.0f);

		// This function should be called once per frame with the real measured frame time delta in seconds. 
		void Update(float dtRealSeconds);

		void singleStep();

		//get
		float getTimeScale() const;
		float getDeltaTime() const;
		bool isPaused() const;
		unsigned long long getTimeCycles() const;


		//set
		void setPaused(bool isPaused);
		void setTimeScale(float scale);
		
		// Determine the difference between this clock’s absolute time and that of another clock, in seconds.
		float calcDeltaSeconds(const Clock& other);
		

};


} 

#include "Clock.inl"

#endif