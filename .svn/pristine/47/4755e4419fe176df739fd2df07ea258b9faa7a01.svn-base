#ifndef _ACTOR_H
#define _ACTOR_H

#include <string>
#include"Vector3.h"
#include"ActorController.h"
#include"GameLoop.h"
#include"BoundingBox.h"
#include"EventHandler.h"
#include"../../../Code/Renderer/cMainWindow.h"

class Entity;
class ActorController;
class BoundingBox;

namespace Engine
{

class Actor
{

private:

	 Vector3 *position;
	 Vector3 *previousPosition;
	 Vector3 *m_velocity;
	 Vector3 *m_previousVelocity;
	 Vector3 *m_acceleration;
	
	 Vector3 *color;
	 int m_ID;
	 float rotation;

	 cs6963::Entity *m_entity;
	 std::string meshFile;
	 std::string textureFile;

	 BoundingBox *m_box;

	 Actor(const Actor &);
	 //void operator=( const Actor&);

public:

    Actor(){}

	ActorController *controller;

	static Actor * CreateActor(const Vector3 i_position, ActorController *const controller, std::string mesh, std::string texture, int i_ID);
  
	static Actor * CreateActor(Actor *parent, const Vector3 i_position, ActorController *const controller, int key, int i_ID);
  
	void TransLatePosition(D3DXVECTOR3 offset);

	Vector3*  getActorPosition();
	
	Vector3*  getActorPreviousPosition();

	void setActorPosition(const Vector3 & c);
	void setActorPreviousPosition(const Vector3& v);

	Vector3*  getActorVelocity();
	
	Vector3 * getActorPreviousVelocity();

	void setActorVelocity(const Vector3 & i_velocity);

	Vector3*  getActorAcceleration();
	
	void setActorAcceleration(const Vector3 & i_acceleration);

	Vector3*  getActorColor();

	void setAssets(std::string i_meshFile, std::string i_textureFile);

	Actor& getThis();

    int getID();

   float getActorRotation();

   void SetCameraBehind();
   void DetectCollision();

   void setActorRotation(float i_rotation);

   void Subscribe(std::string i_message);
  
   void UnSubscribe(std::string i_message);

   void sendMessage(std::string i_message);

	void setController(ActorController *const controller);

	void setBoundingBox(int width,int height, int length, TriggerBoxController *i_boost);

	BoundingBox* getBox();

	void update();

	static Actor* AddToWorld(const Vector3 i_position, ActorController *const controller, std::string i_meshFile, std::string i_textureFile, int i_ID);
	
	Actor* AddToWorld(const Vector3 i_position, ActorController *const controller,int key, int i_ID);

	void EnablePhysics();
	void EnableRenderer();
	void EnableCollision();

	void RemoveFromWorld();
	void DisablePhysics();
	void DisableRenderer();
	void DisableCollision();

	~Actor();
};

}//namespace end

#endif

