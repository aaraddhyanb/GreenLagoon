#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include"Vector3.h"
#include"TriggerBoxController.h"

namespace Engine
{
	class Actor;

	class BoundingBox
	{

	private:

		TriggerBoxController *triggerBox;
		Vector3 min,max;
		int width, height, length;
	
	
	  public:

		BoundingBox();
		BoundingBox(Actor &i_actor,int width, int height,int length, TriggerBoxController *i_boost);
		void operator=(BoundingBox &);
		Vector3 GetMin();
		Vector3 GetMax();
		int GetWidth();
		int GetHeight();
		int GetLength();
		TriggerBoxController *getTrigger();
		void Update(Actor &i_actor);
	
	};

} //namespace end

#endif