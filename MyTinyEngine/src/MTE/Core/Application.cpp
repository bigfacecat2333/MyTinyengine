#include "mtepch.h"
#include "MTE/Core/Application.h"
#include "MTE/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace MTE {

	// std::bind()的作用是将一个函数绑定到一个对象上，返回一个新的可调用对象
	// 这里需要this指针，因为OnEvent是Application的成员函数
	// this是Application的对象，std::placeholders::_1是Event& e
	// 也可以用lambda表达式： [this](Event& e) -> void { OnEvent(e); }
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		// using EventCallbackFn = std::function<void(Event&)>;
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	// glfw回调函数发生后（见WindowsWindow.cpp），会创建一个自定义的event（包含了打印，事件类型，特征的函数调用），并将事件放入到自定义的回调函数
	// OnEvent是发生在WindowsWindow.cpp中的data.EventCallback(event)
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		// Dispatch: 1 判断是否为e和WindowCloseEvent同一个类 2 如果是，调用OnWindowClosed函数
		// WindowCloseEvent是模板中的T，OnWindowClosed是模板中的F
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		// 也可以用lambda表达式： dispatcher.Dispatch<WindowCloseEvent>([this](Event& e) -> bool { return OnWindowClosed(e); });

		// 栈顶的layer先处理，如果没有处理，就交给下一个layer处理
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		// render loop
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// render loop
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}