#pragma once

#include "MTE/Core.h"

#include <string>
#include <functional>

namespace MTE {
	// Events are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		// ��EventType����
		None = 0,
		EventCategoryApplication =		BIT(0),
		EventCategoryInput =			BIT(1),
		EventCategoryKeyboard =			BIT(2),
		EventCategoryMouse =			BIT(3),
		EventCategoryMouseButton =		BIT(4)
	};

// ʵ��GetEventType GetName GetCategoryFlags
// #�Ĺ����ǽ������ĺ���������ַ�����������Stringfication��
// ##����Ϊ���ӷ���concatenator��������������Token����Ϊһ��Token��
// #define PRINT( n ) printf( "token" #n " = %d", token##n ) PRINT(mine ) printf( "token" "mine" " = %d", tokenmine );
// ��ľ�̬��Ա��������̬��Ա�����Ǻ�����صģ������Ǻ���ľ��������صġ���ʹû�о������Ҳ�ܵ�����ľ�̬��Ա�����ͳ�Ա������ -> ���������Ҫ����ģ����
// һ����ľ�̬������������һ��ȫ�ֺ�����ֻ�����������������ڰ��������ļ���
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

// ������ж�
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class MTE_API Event
	{
	public:
		virtual ~Event() = default;

		// ͨ��EVENT_CLASS_TYPE��ʵ��
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		
		// ToString ֻ��һ��������Եĺ���
		virtual std::string ToString() const { return GetName(); }
		
		// �ж��Ƿ���ĳ������
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		// �鿴�Ƿ񱻴�����
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		// renference��֤�κ�Event����
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		// ģ��ʵ��callback
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// ��Ϊ��static���������Կ�����T::GetStaticType()
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}