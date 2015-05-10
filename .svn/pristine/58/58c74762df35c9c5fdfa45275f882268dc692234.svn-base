#include"Vector2.h"

float Engine::Vector2::Length()
{
	float o_value=  pow(x,2) +pow(y,2);
    return sqrt(o_value);
}


Engine::Vector2 Engine::Vector2::Normalize()
{
    float length= Length();

	float temp =x/length;
	float tempy=y/length;
	return Vector2(x/length,y/length);
}
