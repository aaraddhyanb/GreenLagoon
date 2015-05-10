#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>

#include"Vector3.h"
#include<fmod.h>
#include"fmod.hpp"
#include"fmod_errors.h"

typedef FMOD::Channel* MChannel;

struct ChannelData
{
	FMOD::Channel * channel;
	Engine::Vector3 *listenerPos;
	Engine::Vector3 *sourcePos;
};

namespace Engine
{
    class SoundManager
    { 
	private:
		
		static SoundManager *singleton;
	
		FMOD::System *system;
		FMOD_RESULT result;
		unsigned int version;
		int numDrivers;
		FMOD_SPEAKERMODE speakerMode;
		FMOD_CAPS caps;
		char name[256];

		std::vector<ChannelData> channelList;
		std::vector<MChannel> channel2DList;

		//Private constructors 
		SoundManager(){}
		SoundManager(const SoundManager &i_object);
		void operator=(const SoundManager &i_object);

	  public:

		float musicVolume;
		float sfxVolume;

		static SoundManager& Manager()
		{
			if(singleton==NULL)
			{
				singleton= new SoundManager();
				return *singleton;
			}
			return *singleton;
		}

		void Init();
		void PlayOneShot(std::string soundName);
		FMOD::Channel* PlayLoop3D(std::string soundName, Engine::Vector3 *sourcePosition, Engine::Vector3* listenerPosition );
		void PlayLoop2D(std::string soundName);
		void PauseChannel(FMOD::Channel * channel, bool predicate);
		void PlayOnChannel(FMOD::Channel * channel, std::string soundName);
		void ChangeAudioOnChannel(MChannel channelName, std::string soundName );
		void SetMusicVolume(float value);
		void SetSfxVolume(float value);
		void Update();
		void Release();
   };
}
#endif