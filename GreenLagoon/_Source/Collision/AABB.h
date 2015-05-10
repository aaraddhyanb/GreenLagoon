#ifndef AABB_H
#define AABB_H

#include"BoundingBox.h"
#include"Vector2.h"
#include"Actor.h"

namespace Engine
{
	class BoundingBox;
	class Actor;

	class AABB
	{

	  private:
	
		
	    static bool collided;
		static bool normalXSwaped;
		static bool normalYSwaped;
		static Vector3 sideNormal;

	  public:

		
		static bool isCollided();
		static Vector3 checkNormal();
		static bool CheckForCollision(Actor &i_boxA,Actor &i_boxB,float deltaTime);
		static bool CheckForCollision(Actor &i_actorA,Vector3 i_positionA,Vector3 i_positionB, Vector3 i_velocityA,Vector3 i_velocityB,float i_width,float i_height,float deltaTime);

	};

}
#endif