#include"SoundManager.h"

namespace Engine{

SoundManager *SoundManager::singleton=NULL;

void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        //std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

void SoundManager::Init()
{
	result = FMOD::System_Create(&system);
	FMODErrorCheck(result);

	// Get number of sound cards
	result = system->getNumDrivers(&numDrivers);
	FMODErrorCheck(result);

	// No sound cards (disable sound)
	if (numDrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(result);
	}

	// At least one sound card
	else
	{
		// Get the capabilities of the default (0) sound card
		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODErrorCheck(result);
 
		// Set the speaker mode to match that in Control Panel
		result = system->setSpeakerMode(speakerMode);
		FMODErrorCheck(result);
	}

	// Increase buffer size if user has Acceleration slider set to off
	if (caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = system->setDSPBufferSize(1024, 10);
		FMODErrorCheck(result);
	}

	 // Get name of driver
    result = system->getDriverInfo(0, name, 256, 0);
    FMODErrorCheck(result);
 
	 // Initialise FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);

	musicVolume=0;
	sfxVolume=0;
}

void SoundManager::PlayOneShot(std::string soundName)
{
	FMOD::Sound *audio;
	FMOD::Channel *channel=0;

	system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &audio);
	system->playSound(FMOD_CHANNEL_FREE, audio, false, &channel);
	channel->setVolume(sfxVolume); 
}

void SoundManager::PlayLoop2D(std::string soundName)
{
	FMOD::Sound *audio;
	FMOD::Channel *channel=0;

	system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &audio);
	system->playSound(FMOD_CHANNEL_FREE, audio, false, &channel);
	channel->setVolume(musicVolume); 
	channel2DList.push_back(channel);
}

void SoundManager::SetMusicVolume(float value)
{
	musicVolume=value;

	for(int i=0; i<channel2DList.size(); ++i)
	{
		channel2DList[i]->setVolume(musicVolume);
	}
	for(int i=0; i<channelList.size(); ++i)
	{
		channelList[i].channel->setVolume(musicVolume);
	}
}

void SoundManager::SetSfxVolume(float value)
{
	sfxVolume=value;
}

void SoundManager::ChangeAudioOnChannel(MChannel channelName, std::string soundName )
{
	FMOD::Sound *audio;
	system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL|FMOD_3D, 0, &audio);
	system->playSound(FMOD_CHANNEL_REUSE, audio, false, &channelName);
	channelName->setVolume(musicVolume);
}

FMOD::Channel* SoundManager::PlayLoop3D(std::string soundName, Engine::Vector3 *sourcePosition, Engine::Vector3* listenerPosition )
{
	FMOD::Sound *audio;
	FMOD::Channel *channel=0;

	system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL|FMOD_3D, 0, &audio);
	system->playSound(FMOD_CHANNEL_FREE, audio, false, &channel);
	
	channel->setVolume(musicVolume); 
	
	//need this for sound fall off
	channel->set3DMinMaxDistance(50,10000);

	//update position
	//position of listener needed for spatial & reverb effects
	//velocity of listener needed for dopper effects
	FMOD_VECTOR  listenerpos  = { listenerPosition->getx(), listenerPosition->gety(), listenerPosition->getz() };
    system->set3DListenerAttributes(0, &listenerpos, 0, 0, 0);

	ChannelData newChannel;
	newChannel.channel=channel;
	newChannel.listenerPos=listenerPosition;
	newChannel.sourcePos= sourcePosition;
	channelList.push_back(newChannel);

	return channel;
}


void SoundManager::Update()
{
	system->update();

	for(int i=0; i< channelList.size(); ++i)
	{
		if(channelList[i].channel)
		{
			//update listener position
			FMOD_VECTOR  listenerpos  = { channelList[i].listenerPos->getx(), channelList[i].listenerPos->gety(), channelList[i].listenerPos->getz() };
			system->set3DListenerAttributes(0, &listenerpos, 0, 0, 0);

			//update source position
			FMOD_VECTOR  sourcePos  = { channelList[i].sourcePos->getx(), channelList[i].sourcePos->gety(), channelList[i].sourcePos->getz() };

			//source is fixed so velocity is zero
			channelList[i].channel->set3DAttributes(&sourcePos,0);
		}
	}
}

void SoundManager::PauseChannel(FMOD::Channel * channel, bool predicate)
{
	channel->setPaused(predicate);
}

void SoundManager::PlayOnChannel(FMOD::Channel * channel, std::string soundName)
{
	FMOD::Sound *audio;

	system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL|FMOD_3D, 0, &audio);
	system->playSound(FMOD_CHANNEL_FREE, audio, false, &channel);
}


void SoundManager::Release()
{
	system->release();
}

} //namespace end