#include"BoundingBox.h"
#include"Actor.h"

namespace Engine{


BoundingBox::BoundingBox()
{
	min=Vector3(0,0,0);
	max=Vector3(0,0,0);
}

BoundingBox::BoundingBox(Actor &i_actor, int i_width, int i_height, int i_length, TriggerBoxController *i_boost)
{
	this->width=i_width;
	this->height=i_height;
	this->length= i_length;
	this->triggerBox=i_boost;
	min.setx(i_actor.getActorPosition()->getx()-(width/2) );
	max.setx(i_actor.getActorPosition()->getx()+(width/2) );
	min.sety(i_actor.getActorPosition()->gety()-(height/2) );
	max.sety(i_actor.getActorPosition()->gety()+(height/2) );
	min.setz(i_actor.getActorPosition()->getz()-(length/2) );
	max.setz(i_actor.getActorPosition()->getz()+(length/2) );
}



void BoundingBox::Update(Actor &i_actor)
{
	min.setx(i_actor.getActorPosition()->getx()-(width/2) );
	max.setx(i_actor.getActorPosition()->getx()+(width/2) );
	min.sety(i_actor.getActorPosition()->gety()-(height/2) );
	max.sety(i_actor.getActorPosition()->gety()+(height/2) );
	min.setz(i_actor.getActorPosition()->getz()-(length/2) );
	max.setz(i_actor.getActorPosition()->getz()+(length/2) );
}

Engine::Vector3 BoundingBox::GetMin()
 {
	 return min;
 }


Engine::Vector3 BoundingBox::GetMax()
 {
	 return max;
 }


 int BoundingBox::GetWidth()
 {
	 return width;
 }
  
 int BoundingBox::GetHeight()
 {
	 return height;
 }

 int BoundingBox::GetLength()
 {
	 return length;
 }

 TriggerBoxController * BoundingBox::getTrigger()
 {
	 return triggerBox;
 }


} //namespace end