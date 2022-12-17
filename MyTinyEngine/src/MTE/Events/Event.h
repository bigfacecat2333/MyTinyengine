#pragma once

#include "MTE/Core.h"

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
		// 将EventType过滤
		None = 0,
		EventCategoryApplication =		BIT(0),
		EventCategoryInput =			BIT(1),
		EventCategoryKeyboard =			BIT(2),
		EventCategoryMouse =			BIT(3),
		EventCategoryMouseButton =		BIT(4)
	};

// 实现GetEventType GetName GetCategoryFlags
// #的功能是将其后面的宏参数进行字符串化操作（Stringfication）
// ##被称为连接符（concatenator），用来将两个Token连接为一个Token。
// #define PRINT( n ) printf( "token" #n " = %d", token##n ) PRINT(mine ) printf( "token" "mine" " = %d", tokenmine );
// 类的静态成员函数、静态成员变量是和类相关的，而不是和类的具体对象相关的。即使没有具体对象，也能调用类的静态成员函数和成员变量。 -> 这个特性主要用于模板编程
// 一般类的静态函数几乎就是一个全局函数，只不过它的作用域限于包含它的文件中
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

// 对类的判断
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class MTE_API Event
	{
	public:
		virtual ~Event() = default;

		// 通过EVENT_CLASS_TYPE来实现
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		
		// ToString 只是一个方便调试的函数
		virtual std::string ToString() const { return GetName(); }
		
		// 判断是否是某个类型
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		// 查看是否被处理了
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		// renference保证任何Event进入
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		// 模板实现callback
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// 因为是static函数，所以可以用T::GetStaticType()
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