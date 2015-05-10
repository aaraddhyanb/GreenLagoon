#include"Actor.h"

#define scene cs6963::cMainWindow::GetSingleton().m_renderer.scene 

Engine::Actor * Engine::Actor::CreateActor(const Engine::Vector3 i_position, ActorController * const control, std::string i_meshFile, std::string i_textureFile, int i_ID) 
{
   Actor *actor=new Actor();
   actor->meshFile=i_meshFile;
   actor->textureFile=i_textureFile;
   actor->m_entity=scene->AddEntity(actor->meshFile, actor->textureFile, i_position.getx(), i_position.gety(), i_position.getz(), 0);
   actor->position=new Vector3(i_position);
   actor->previousPosition=new Vector3(i_position);
   actor->m_velocity=new Vector3(0.0f,0.0f,0.0f);
   actor->m_previousVelocity=new Vector3(0.0,0.0,0.0);
   actor->m_acceleration=new Vector3(0.0f,0.0f,0.0f);
   actor->m_box=NULL;
   actor->controller=control;
   actor->rotation=0;

  actor->m_ID=i_ID;

  return actor;
}

Engine::Actor * Engine::Actor::CreateActor(Actor *parent, const Vector3 i_position, ActorController *const control, int key,int i_ID) 
{
   Actor *actor=new Actor();
   actor->m_entity=scene->AddEntityToScene(parent->m_entity, key);
   actor->position=new Vector3(actor->m_entity->getMesh()->GetPosition().x,
							   actor->m_entity->getMesh()->GetPosition().y,
							   actor->m_entity->getMesh()->GetPosition().z);
   actor->previousPosition=new Vector3(i_position);
   actor->m_velocity=new Vector3(0.0f,0.0f,0.0f);
   actor->m_previousVelocity=new Vector3(0.0,0.0,0.0);
   actor->m_acceleration=new Vector3(0.0f,0.0f,0.0f);
   actor->m_box=NULL;
   actor->controller=control;
   actor->rotation=0;

  actor->m_ID=i_ID;

  return actor;
}

void  Engine::Actor::setAssets(std::string i_meshFile, std::string i_textureFile)
{
	meshFile= i_meshFile;
	textureFile= i_textureFile;
}

int Engine::Actor::getID()
{
	return (m_ID);
}

Engine::Vector3 * Engine::Actor::getActorVelocity()
{
	return (m_velocity);
}

Engine::Vector3 * Engine::Actor::getActorPreviousVelocity()
{
	return (m_previousVelocity);
}

void Engine:: Actor:: setActorVelocity(const Vector3 & i_velocity)
{
	 *m_previousVelocity=*m_velocity;
	 *m_velocity=i_velocity;
}


Engine::Vector3 * Engine::Actor::getActorAcceleration()
{
	return (m_acceleration);
}


void Engine:: Actor:: setActorAcceleration(const Vector3 & i_acceleration)
{
	 *m_acceleration=i_acceleration;
}


Engine::Vector3 * Engine::Actor::getActorPosition()
{
	return (position);
}

Engine::Vector3 * Engine::Actor::getActorPreviousPosition()
{
	return (previousPosition);
}

void Engine:: Actor:: setActorPosition(const Vector3 & v)
{     
	*position=v;
	m_entity->getMesh()->SetPosition(v.getx(), v.gety(), v.getz());
}

void Engine:: Actor::setActorPreviousPosition(const Vector3 &v)
{     
	*previousPosition=v;
}

float Engine::Actor::getActorRotation()
{
	return (rotation);
}

void Engine::Actor::setActorRotation(float i_rotation)
{
	//	while( rotation > 360.0f )
	//			rotation -= 360.0f;

	rotation=i_rotation;
}

Engine::Vector3 * Engine::Actor::getActorColor()
{
	return (color);
}

void Engine::Actor::Subscribe(std::string i_message)
{
	Singleton<World>::getInstance().EnableEventHandler(i_message,*this);
}

void Engine::Actor::UnSubscribe(std::string i_message)
{
	Singleton<World>::getInstance().DisableEventHandler(i_message,*this);
}

 void Engine::Actor::sendMessage(std::string i_message)
 {
	 if(controller)
	controller->OnMessage(i_message,*this);
	
 }

 void Engine::Actor::SetCameraBehind()
 {
	 scene->camera->Follow(m_entity->getMesh());
 }

void Engine::Actor::DetectCollision()
{
	m_entity->getMesh()->detectCollision();
}

void Engine::Actor::TransLatePosition(D3DXVECTOR3 offset)
{
	m_entity->getMesh()->Translate(offset);
	position->setx(m_entity->getMesh()->GetPosition().x);
	position->sety(m_entity->getMesh()->GetPosition().y);
	position->setz(m_entity->getMesh()->GetPosition().z);
}

void Engine::Actor::update()
{
	if(controller)
	controller->updateActor(* this);
	if(m_box)
	m_box->Update(*this);

	if(m_entity->getMesh())
	    m_entity->getMesh()->SetRotation(rotation);
}

void  Engine::Actor::setController(ActorController *const controllerChange)
{
	controller=controllerChange;
}

void  Engine::Actor::setBoundingBox(int i_width,int i_height, int i_length, TriggerBoxController *i_boost)
{
	if(!m_box)
     m_box=new BoundingBox(*this,i_width,i_height, i_length, i_boost);
}


 Engine::BoundingBox*  Engine::Actor::getBox()
 {
	 return m_box;
 }

 Engine::Actor & Engine::Actor::getThis()
 {
	 return *this;
 }
 
 Engine::Actor* Engine::Actor::AddToWorld(const Vector3 i_position, ActorController *const controller, std::string i_meshFile, std::string i_textureFile, int i_ID)
{
	Actor * o_Actor=Singleton<World>::getInstance().AddActor(i_position,controller,i_meshFile,i_textureFile,i_ID);
	return o_Actor;
 }

 Engine::Actor* Engine::Actor::AddToWorld(const Vector3 i_position, ActorController *const controller,int key, int i_ID)
 {
	 Actor * o_Actor=Singleton<World>::getInstance().AddActor(this, i_position,controller, key,i_ID);
	 return o_Actor;
 }

  void Engine::Actor::EnablePhysics()
{
	Singleton<World>::getInstance().EnablePhysics(*this);
 }

  void Engine::Actor::EnableRenderer()
{
	Singleton<World>::getInstance().EnableRenderer(*this);
 }
	
 void Engine::Actor::EnableCollision()
{
		Singleton<World>::getInstance().EnableCollision(*this);
}
	

 void Engine::Actor::RemoveFromWorld()
{
	Singleton<World>::getInstance().RemoveActor(*this);
}

  void Engine::Actor::DisablePhysics()
{
		 Singleton<World>::getInstance().DisablePhysics(*this);
 }

  void Engine::Actor::DisableRenderer()
{
	Singleton<World>::getInstance().DisableRenderer(*this);
 }
	
 void Engine::Actor::DisableCollision()
{
	 Singleton<World>::getInstance().DisableCollision(*this);
}

Engine::Actor::~Actor()
{
	delete position;
	delete m_velocity;
	delete m_acceleration;
	delete color;
	delete m_box;

    position=NULL;
	m_velocity=NULL;
	m_acceleration=NULL;
	m_box=NULL;
	
	color=NULL;
	m_ID=0;

}


//
//
//
