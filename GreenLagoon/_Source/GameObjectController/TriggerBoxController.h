#ifndef TRIGGERBOXCONTROLLER_H
#define TRIGGERBOXCONTROLLER_H



namespace Engine
{
	class Actor;
	class Vector3;

	class TriggerBoxController
	{

	  private:

	  public:

      virtual void OnCollision(Actor &i_actor, Actor &withActor)=0;
	  virtual ~TriggerBoxController(){};
	};

} //namespace end

#endif