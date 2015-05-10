#include"GameScene.h"
#include"Actor.h"
#include"SoundManager.h"
#include"WaypointsData.h"
#include"PathFinding.h"
#include"PlayerController.h"
#include"SmartAIController.h"
#include"JumpTrigger.h"
#include"StairTrigger.h"
#include"PlayerCollisionFlagController.h"
#include"WorldController.h"
#include"PlayerTrigger.h"
#include"MonsterTrigger.h"
#include"RingBuffer.h"
#include<vector>
#include"GameLoop.h"
#include"Matrix.h"
#include"../Code/Renderer/RendererWidgets.h"

#include<stdlib.h>
#include<crtdbg.h>
#include<libconfig.h>
#include<Windows.h>

using namespace Engine;

int WINAPI  WinMain(HINSTANCE i_thisInstanceOfTheApplication, HINSTANCE i_thisIsNothing, char* i_commandLineArguments, int i_initialWindowDisplayState )
{
   #if defined _PROFILE
	Profile profileInstance;
	profileInstance.StartTick();
   #endif
   
	//Initializing engine
	Init( i_thisInstanceOfTheApplication,  i_thisIsNothing, i_commandLineArguments,  i_initialWindowDisplayState);

	WorldController *world= new WorldController();
	SmartAIController *monster  = new SmartAIController();
	PlayerController * player = new PlayerController();
	PlayerTrigger *flagControls=new PlayerTrigger();
	MonsterTrigger *monsterFlagControls= new MonsterTrigger();
	PlayerCollisionFlagController *pickFlag= new PlayerCollisionFlagController();
	StairTrigger *stair= new StairTrigger();

	Vector3 worldpos(0,0,0);
	Vector3 playpos(200,-100,100);
	Vector3 monsterpos(0,-200,0);

	Engine::Actor *ctf_World=Engine::Actor::AddToWorld(worldpos,world,"data/Meshes/mesh.bin", "data/Materials/worldTexture.txt",0);
	Engine::Actor *player_One=Engine::Actor::AddToWorld(playpos,player,"data/Meshes/snowMan.bin", "data/Materials/snowManTexture.txt",1);
	Engine::Actor *monster_One=Engine::Actor::AddToWorld(monsterpos,monster,"data/Meshes/snowMan.bin", "data/Materials/enemyTexture.txt",1001);
	
	monster->player=player_One;
	monster_One->setBoundingBox(70,70,70,monsterFlagControls);
	monster_One->EnableCollision();

	player_One->setBoundingBox(70,30,70,flagControls);
	player_One->EnableCollision();

	std::ifstream file;
	file.open("data/Meshes/changes.txt"); 
			
	std::vector<int> idList;

	std::vector<Engine::Actor *> triggers;
	int triggerIDProvider=100;

	if (!file.fail())
	{
		std::string word;

		while(!file.eof())
		{
			file>>word;
			if(word=="TotalTriggers")
			{
				int size=0;
				file>>size;
				for(int j=0; j< size; ++j)
				{
					file>>word;
					float minx,miny,minz;
					float maxx,maxy,maxz;
					if(word=="MinBB")
					{
						file>>minx>>miny>>minz;
					}
					file>>word;
					if(word=="MaxBB")
					{
						file>>maxx>>maxy>>maxz;
					}
					//Create TriggerBoxes
					Vector3 triggerPos=Vector3( (minx+maxx)/2, (miny+maxy)/2, (minz+maxz)/2 );
					Engine::Actor *trigger=Engine::Actor::AddToWorld(triggerPos,world,"null","null",++triggerIDProvider);
					trigger->setBoundingBox( 50,100,50,pickFlag);
					trigger->EnableCollision();
					triggers.push_back(trigger);
				}
			}
			if(word=="TotalDynamicGameObjects")
			{
				int size=0;
				file>>size;
				for(int j=0; j< size; ++j)
				{
					file>>word;
					int id=-1;
					if(word=="id")
					{
						file>>id;
						assert(id>=0);
						idList.push_back(id);
						word="";
					}
					file>>word;
					file>>word;
					file>>word;
					file>>word;
					file>>word;
					file>>word;
					file>>word;
					file>>word;
				}
			}
		}
	    file.close();
	}

	std::vector<Engine::Actor *> dynamicObjects;

	int idProvider=3;

	Engine::Actor* dynamicActor= ctf_World->AddToWorld(playpos, world ,idList[0], ++idProvider); 
	dynamicActor->setBoundingBox(150,300,150,flagControls);
	dynamicActor->EnableCollision();
	dynamicActor->setActorPreviousPosition(*dynamicActor->getActorPosition());
	dynamicObjects.push_back(dynamicActor);
		
	dynamicActor= ctf_World->AddToWorld(playpos, world ,idList[1], ++idProvider); 
	dynamicActor->setBoundingBox(150,300,150,monsterFlagControls);
	dynamicActor->EnableCollision();
	dynamicActor->setActorPreviousPosition(*dynamicActor->getActorPosition());
	dynamicObjects.push_back(dynamicActor);

	player_One->SetCameraBehind();
	
	//Loading Waypoints
	file.open("data/Meshes/newWaypointGraph.txt"); 
	if (!file.fail())
	{
		std::string word;

		while(!file.eof())
		{
			file>>word;
			if(word=="Waypoints")
			{
				int size=0;
				file>>size;
				for(int j=0; j< size; ++j)
				{
					int id;
					float posx,posy,posz;

					file>>id>>posx>>posy>>posz;
					//Add waypoint
					Engine::WaypointsData::Manager().AddWaypoint(id, posx, posy, posz);
				}
			}
			if(word=="Links")
			{
				int size=0;
				file>>size;
				for(int j=0; j< size; ++j)
				{
					int point1,point2;
					float distance;
					file>>point1>>point2>>distance;

					//add Link
					Engine::WaypointsData::Manager().AddLink(point1, point2, distance);
				}
			}
		}
	    file.close();
	}

	monster->flagPosition=Vector3(dynamicObjects[1]->getActorPosition()->getx(), dynamicObjects[1]->getActorPosition()->gety(),dynamicObjects[1]->getActorPosition()->getz() );
	monster->homePosition=Vector3(dynamicObjects[0]->getActorPosition()->getx(), dynamicObjects[0]->getActorPosition()->gety(),dynamicObjects[0]->getActorPosition()->getz() );


	idProvider=200;
	Engine::Vector3 triggerPositions[5];
	triggerPositions[0].setx(51.1f);
	triggerPositions[0].sety(-207.0f);
	triggerPositions[0].setz(845.08f);

	triggerPositions[1].setx(-631.0f);
	triggerPositions[1].sety(-207.0f);
	triggerPositions[1].setz(1567.98f);

	triggerPositions[2].setx(-329.17f);
	triggerPositions[2].sety(-207.0f);
	triggerPositions[2].setz(-1545.23f);

	triggerPositions[3].setx(-132.4f);
	triggerPositions[3].sety(-207.0f);
	triggerPositions[3].setz(-823.0f);

	triggerPositions[4].setx(524.26f);
	triggerPositions[4].sety(-207.0f);
	triggerPositions[4].setz(-1572.37f);

	JumpTrigger *jump=new JumpTrigger();
	for(int j=0; j< 5; ++j)
	{
		Engine::Actor *jumpBox=Engine::Actor::AddToWorld(triggerPositions[j],world,"null", "null",++idProvider);
		jumpBox->setBoundingBox(100,40,140,jump);
		jumpBox->EnableCollision();
		jumpBox->setActorPreviousPosition(*jumpBox->getActorPosition());
	}	


	//Steps Soft sound
	file.open("data/Meshes/steps.txt"); 
		while(!file.eof())
		{
			std::string word;
			file>>word;
			if(word=="TotalTriggers")
			{
				int size=0;
				file>>size;
				for(int j=0; j< size; ++j)
				{
					file>>word;
					float minx,miny,minz;
					float maxx,maxy,maxz;
					if(word=="MinBB")
					{
						file>>minx>>miny>>minz;
					}
					file>>word;
					if(word=="MaxBB")
					{
						file>>maxx>>maxy>>maxz;
					}
					//Create TriggerBoxes
					Vector3 triggerPos=Vector3( (minx+maxx)/2, (miny+maxy)/2, (minz+maxz)/2 );
					Engine::Actor *trigger=Engine::Actor::AddToWorld(triggerPos,world,"null","null",4000);
					trigger->setBoundingBox( maxx-minx,maxy-miny,maxz-minz,stair);
					trigger->EnableCollision();
				}
			}
		}
	    file.close();
	
	//Play background sound
	SoundManager::Manager().PlayOneShot("welcome.wav");
	SoundManager::Manager().PlayLoop2D("background.wav");
	MonsterTrigger::SetChannel("robot.mp3", monster_One, player_One);
	player->playerHardSurfaceChannel=player->SetChannel( player->playerHardSurfaceChannel, "runningHardSurface.wav", player_One, player_One);
    player->playerSoftSurfaceChannel=player->SetChannel( player->playerSoftSurfaceChannel, "runningSoftSurface.wav", player_One, player_One);
	player->playerPantingChannel=player->SetChannel( player->playerPantingChannel, "panting.wav", player_One, player_One);


	bool bQuit = false;
	do
	{
		if( !bQuit )
		{
			//Engine::consoleWindowPrintf(1, "pos %f %f %f", player_One->getActorPosition()->getx(), player_One->getActorPosition()->gety(), player_One->getActorPosition()->getz() );
		    
			//updating all the actors
			Update();
		}

	} while ( (bQuit == false)  );


	//Shutdown 
	{

		//Shuting down player only
		//player_One->RemoveFromWorld();
		//player_One->DisablePhysics();
		//player_One->DisableRenderer();
		//player_One->DisableCollision();
	
		//This shutdown should delete all the monsters.
		//Intentionally left all monsters for shutdown to check the robustness
		//of the system's sharedpointer auto-deletion.
		Shutdown();

		 //delete player;
		 //delete smonster;
		 //delete boost;

		 //Destroying Memory pool
		 MemoryPool::DestroyMemoryPool();

		  #if defined _PROFILE
			profileInstance.StopTick();
			float tick=profileInstance.DifferenceInTick();
			consoleWindowPrintf(2,"Tick: %f",tick);
		   #endif
	}
}

