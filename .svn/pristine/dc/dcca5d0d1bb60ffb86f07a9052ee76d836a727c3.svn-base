namespace Engine
{

 unsigned long long Clock::secondsToCycles(float timeSeconds)  
{  
	return (unsigned long long)(timeSeconds * s_cyclesPerSecond);
}


//Only use to convert small durations into seconds. 
float Clock::cyclesToSeconds(unsigned long long timeCycles) 
{  
	return (float)timeCycles / s_cyclesPerSecond; 
}

 float Clock::ReadHiResTimerFrequency()
{
	LARGE_INTEGER i;
	QueryPerformanceFrequency(&i);
	return static_cast<float>(i.QuadPart);
}

 unsigned long long Clock::GetCurrentCycleTime()
{
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	return i.QuadPart;
}



} //namespace