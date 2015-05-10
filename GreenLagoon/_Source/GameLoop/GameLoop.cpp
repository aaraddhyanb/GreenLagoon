#include"GameLoop.h"
#include<libconfig.h>

namespace Engine
{
	Renderer *Singleton<Renderer>::m_instance=NULL;
	Physics * Singleton<Physics>::m_instance=NULL;
	Collision *Singleton<Collision>::m_instance=NULL;
	Time * Singleton<Time>::m_instance=NULL;
	World * Singleton<World>::m_instance=NULL;
	EventHandler *Singleton<EventHandler>::m_instance=NULL;
	float Time::deltaTime = 0;
    float Clock::s_cyclesPerSecond = 0;
	int  Renderer::width=0;
	int  Renderer::height=0;
	
	void Init(HINSTANCE i_thisInstanceOfTheApplication, HINSTANCE i_thisIsNothing, char* i_commandLineArguments, int i_initialWindowDisplayState)
	{
		config_t cfg;
		int Screenwidth;
		int Screenheight;
		config_init(&cfg);

		if(! config_read_file(&cfg, "config.cfg"))
		{
			fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
							config_error_line(&cfg), config_error_text(&cfg));
			config_destroy(&cfg);
		}
		config_lookup_int(&cfg, "ScreenWidth", &Screenwidth);
		config_lookup_int(&cfg, "ScreenHeight", &Screenheight);
		  
		config_destroy(&cfg);
		Renderer::width=Screenwidth;
		Renderer::height=Screenheight;

		Singleton<Time>::getInstance().Init();
		Singleton<Physics>::getInstance().Init();
		Singleton<Renderer>::getInstance().Init( i_thisInstanceOfTheApplication, i_thisIsNothing,  i_commandLineArguments,  i_initialWindowDisplayState);
		Singleton<World>::getInstance().Init();
		Singleton<Collision>::getInstance().Init();
		Singleton<EventHandler>::getInstance().Init();
		SoundManager::Manager().Init();
	}

	bool Update()
	{
		Singleton<Time>::getInstance().Update();
		float f = Singleton<Time>::getInstance().getDeltaTime();
		Engine::consoleWindowPrintf(3, "\nFRame rate:%f",1/f);

		Singleton<Physics>::getInstance().Update(Singleton<Time>::getInstance().getDeltaTime() );
		Singleton<Collision>::getInstance().Update(Singleton<Time>::getInstance().getDeltaTime() );
		Singleton<Renderer>::getInstance().Update(Singleton<Time>::getInstance().getDeltaTime()  );
		Singleton<World>::getInstance().Update(Singleton<Time>::getInstance().getDeltaTime()  );
		SoundManager::Manager().Update();

		if(BB::isCollided()==true)
		return 1;
		return 0;
	}

	void Shutdown()
	{
		Singleton<Time>::getInstance().Shutdown();
		Singleton<Physics>::getInstance().Shutdown();
		Singleton<Renderer>::getInstance().Shutdown();
		Singleton<World>::getInstance().Shutdown();
		Singleton<Collision>::getInstance().Shutdown();
		Singleton<EventHandler>::getInstance().Shutdown();

		Singleton<Time>::Shutdown();
		Singleton<Physics>::Shutdown();
		Singleton<Renderer>::Shutdown();
		Singleton<World>::Shutdown();
		Singleton<Collision>::Shutdown();
		Singleton<EventHandler>::Shutdown();
	}
}



