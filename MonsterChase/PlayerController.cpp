#include"PlayerController.h"
#include"PlayerTrigger.h"
#include <d3dx9math.h>
#include <d3dx9.h>
#include "../Code/Renderer/RendererWidgets.h"

float PlayerController::playerStamina=10;
playerSound PlayerController::playerSoundStates=playerSound::isRunningOnHardSurface;
FMOD::Channel* PlayerController::playerHardSurfaceChannel;
FMOD::Channel* PlayerController::playerSoftSurfaceChannel;
FMOD::Channel* PlayerController::playerPantingChannel;

bool PlayerController::hasBeenRunningOnHardSurface=true;

using namespace Engine;

void PlayerController::SetMusicVolume(float value)
{
	SoundManager::Manager().SetMusicVolume(value/10);
}
void PlayerController::SetSfxVolume(float value)
{
	SoundManager::Manager().SetSfxVolume(value/10);
}

PlayerController::PlayerController(void)
{
	TextField *text;
	text=new TextField();
	cs6963::cMainWindow::GetSingleton().m_renderer.AddText(text, "Player:", 100, 700, &getScore);

	TextField *stamina;
	stamina=new TextField();
	cs6963::cMainWindow::GetSingleton().m_renderer.AddText(stamina, "Stamina:", 100, 750, &getStamina);

	RendererWidgets::Singleton().AddSlider("Music Volume:",1000, 20, 0, 10, &SetMusicVolume);
    RendererWidgets::Singleton().AddSlider("Sfx Volume:", 1000, 70, 0, 10, &SetSfxVolume);

	playerSoundStates=playerSound::isRunningOnHardSurface;
}

FMOD::Channel* PlayerController::SetChannel(FMOD::Channel* channel, std::string soundName, Engine::Actor* source, Engine::Actor* listener)
{
	channel= SoundManager::Manager().PlayLoop3D(soundName, source->getActorPosition(), listener->getActorPosition());
	return channel;
}

float PlayerController::getScore()
{
	return PlayerTrigger::playerScore;
}

float PlayerController::getStamina()
{
	return PlayerController::playerStamina;
}

void PlayerController:: updateActor(Engine::Actor & actor)
{	
	actor.DetectCollision();

	bool predicate;
	playerHardSurfaceChannel->getPaused(&predicate);
	playerSoftSurfaceChannel->setPaused(!predicate);

	playerPantingChannel->setPaused(true);
	playerHardSurfaceChannel->setPaused(true);

	if(PlayerController::playerStamina<10.0f)
		PlayerController::playerStamina+=0.05f;

	D3DXVECTOR3 offset(0.0f, 0.0f, 0.0f);
	float speed=1.0f;

	if( GetAsyncKeyState(0x57) ) //W
	{
		 if(GetAsyncKeyState(VK_SHIFT))
		 {
			 if(PlayerController::playerStamina>=2.0f)
			 {
				playerPantingChannel->setPaused(false);
				speed=1.8f;
				PlayerController::playerStamina-=0.2f;
			 }
		 }
		offset.x += sin(actor.getActorRotation()) *100.f *speed;
        offset.z += cos(actor.getActorRotation()) *100.f *speed;
	}
	else if( GetAsyncKeyState(0x53) )  //S
	{
		 if(GetAsyncKeyState(VK_SHIFT))
		 {
			 if(PlayerController::playerStamina>=2.0f)
			 {
				playerPantingChannel->setPaused(false);
				speed=1.8f;
				PlayerController::playerStamina-=0.2f;
			 }
		 }
		offset.x -= sin(actor.getActorRotation()) *100.f *speed;;
        offset.z -= cos(actor.getActorRotation()) *100.f *speed;;
	}
	else
	{
		playerPantingChannel->setPaused(true);
		playerHardSurfaceChannel->setPaused(true);
		//playerSoftSurfaceChannel->setPaused(true);
	}

	if( GetAsyncKeyState(0x41) )  //A
	{
		  actor.setActorRotation(actor.getActorRotation()-0.15f);
			if(actor.getActorRotation()<-360.f)
				actor.setActorRotation(actor.getActorRotation()+ 360.f);    
	}
    if( GetAsyncKeyState(0x44) ) //D
	{
		actor.setActorRotation(actor.getActorRotation()+0.15f);
			if(actor.getActorRotation()>360.f)
				actor.setActorRotation(actor.getActorRotation()- 360.f);
	 }

	 if( GetAsyncKeyState(VK_SPACE) )
	 {
		offset.y +=100.0f;
     }

	float movement = 2.0f;


    offset *= (movement * g_time.GetSecondsElapsedThisFrame() );
	//rotation=-9;// += g_time.GetSecondsElapsedThisFrame();

	//if(offset.x || offset.y || offset.z)
	//	playerPosChanged=true;

	actor.TransLatePosition(offset);
		
}
    
void PlayerController::OnMessage(std::string i_message,Engine::Actor &i_actor)
{
	if(i_message=="Kill Monster")
	Singleton<World>::getInstance().RemoveActor(i_actor);
}