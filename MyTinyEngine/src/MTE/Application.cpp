#include "Application.h"

#include <MTE/Events/ApplicationEvent.h>
#include <MTE/Log.h>

namespace MTE {
	
	Application::Application() 
	{

	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		MTE_TRACE(e);
		
		while (true);
	}
}