#include <MTE.h>

class Sandbox : public MTE::Application
{
public:
	Sandbox()
	{
		
	}
	
	~Sandbox()
	{
		
	}
};
 

MTE::Application* MTE::CreateApplication()
{
	return new Sandbox();
}