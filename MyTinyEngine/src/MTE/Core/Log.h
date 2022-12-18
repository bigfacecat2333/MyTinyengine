#pragma once
#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace MTE {
	class MTE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;  // static member variable
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// 创建宏定义用于简化日志记录 
// ...表示可变参数 __VA_ARGS__表示将宏中的数据传递过去
// MTE前的::表示全局作用域
#define MTE_CORE_ERROR(...)		::MTE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MTE_CORE_WARN(...)		::MTE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MTE_CORE_INFO(...)		::MTE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MTE_CORE_TRACE(...)		::MTE::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Cient log macros
#define MTE_ERROR(...)			::MTE::Log::GetClientLogger()->error(__VA_ARGS__)
#define MTE_WARN(...)			::MTE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MTE_INFO(...)			::MTE::Log::GetClientLogger()->info(__VA_ARGS__)
#define MTE_TRACE(...)			::MTE::Log::GetClientLogger()->trace(__VA_ARGS__)