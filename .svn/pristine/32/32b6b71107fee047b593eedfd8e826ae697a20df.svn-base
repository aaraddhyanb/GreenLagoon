#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include"ActorController.h"
#include"Renderer.h"

class Actor;

enum playerSound
{
	isPanting,
	isRunningOnHardSurface,
	isRunningOnSoftSurface
};


class PlayerController: public Engine:: ActorController
{
private:
	

public:

    static playerSound playerSoundStates;
	static FMOD::Channel *playerHardSurfaceChannel;
	static FMOD::Channel* playerSoftSurfaceChannel;
	static FMOD::Channel* playerPantingChannel;


	PlayerController(void);

	static float getScore();
	static float getStamina();

	static bool hasBeenRunningOnHardSurface;

	static float playerStamina;

	static void SetMusicVolume(float);
	static void SetSfxVolume(float);
	FMOD::Channel* SetChannel(FMOD::Channel *,std::string soundName, Engine::Actor* source, Engine::Actor* listener);

	virtual ~PlayerController(){}
	virtual void updateActor(Engine::Actor & actor);
	virtual void OnMessage(std::string i_message,Engine::Actor &actor);
	
};


#endif

