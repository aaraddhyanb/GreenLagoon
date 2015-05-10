#ifndef RENDERER_H
#define RENDERER_H

#include<vector>
#include"Actor.h"
#include"Singleton.h"
#include"SharedPointer.h"
#include<libconfig.h>
#include"../../../Code/Renderer/EntryPoint.h"

namespace Engine 
{

    class Actor;

	class Renderer
	{
	  
	 private:

	    friend Singleton<Renderer>;
		std::vector<class SharedPointer<Actor> *> m_SharedPtr;
		
		 HWND hwnd;

		//Private constructors 
		Renderer(){}
		Renderer(const Renderer &i_object);
		void operator=(const Renderer &i_object);

	public:

		static int  width;
		static int  height;
		
		//methods
		void Init(HINSTANCE i_thisInstanceOfTheApplication, HINSTANCE i_thisIsNothing, char* i_commandLineArguments, int i_initialWindowDisplayState);
		void AddActor(SharedPointer<Actor> &i_instance);
		void RemoveActor(Actor &i_instance);
		void Update(float deltaTime);
		void Shutdown();
	};

} //namespace end

#endif