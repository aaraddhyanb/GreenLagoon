#ifndef BB_H
#define BB_H

#include"BoundingBox.h"
#include"Vector3.h"
#include"Actor.h"

namespace Engine
{
	class BoundingBox;
	class Actor;

	class BB
	{
	  private:
		
	    static bool collided;

	  public:
		static bool isCollided();
		static bool CheckForCollision(Actor &i_boxA,Actor &i_boxB,float deltaTime);
		static bool CheckForCollision(Actor &i_actorA,Vector3 i_positionA,Vector3 i_positionB, Vector3 i_velocityA,Vector3 i_velocityB,float i_width,float i_height,float deltaTime);
	};
}
#endif