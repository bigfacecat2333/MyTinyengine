#pragma once

#include "mtepch.h"
#include "MTE/Events/Event.h"

#include <sstream>

namespace MTE {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(
			const std::string& title = "My Tiny Engine",
			uint32_t width = 2000,
			uint32_t height = 1600)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class MTE_API Window  // interface: ȫ�Ǵ��麯��
	{
	public:
		// using ��ʾȡһ������: �ص�������һ������Ϊvoid������ΪEvent&�ĺ���
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// �ɲ�ͬ��platform��ʵ��
		static Window* Create(const WindowProps& props = WindowProps());
		// static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}