
const float _epsilon=0.00001f;

bool Engine::IsNAN( const float i_val )
{
	volatile float val = i_val;

	return val != val;
}

bool  Engine::isinf(float value)
{
return std::numeric_limits<float>::has_infinity &&
value == std::numeric_limits<float>::infinity();
}

bool Engine::areRelativelyEqual( float val1, float val2 , float i_epsilon =_epsilon)
{
	return fabs(val1 - val2) < i_epsilon;
}

void Engine::consoleWindowPrintf(unsigned int debug_level,const char *fmt, ...)
{
	assert(debug_level!=NULL);
	
	 if(debug_level>=DEBUG_LEVEL)
	 {
	   assert(fmt!=NULL);

	   const unsigned int str_len=128;

	   char str[str_len];

	   va_list args;

       va_start(args,fmt);

	   vsprintf_s(str, str_len,fmt, args);

	   va_end(args);

	   OutputDebugStringA(str);
	 }

}
