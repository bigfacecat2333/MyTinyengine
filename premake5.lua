-- workspace 表示一个工作区，可以包含多个项目
workspace "MyTinyEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

-- Debug windows x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MyTinyEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MyTinyEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MyTinyEngine/vendor/imgui"
-- include premake file 的位置 copy from glfw premake5.lua
include "MyTinyEngine/vendor/GLFW"
include "MyTinyEngine/vendor/Glad"
include "MyTinyEngine/vendor/imgui"

-- project 表示一个项目，可以包含多个文件
project "MyTinyEngine"
	-- location 表示项目的位置 vcxproj所在位置
	location "MyTinyEngine"
	-- dll
	kind "SharedLib"
	language "C++"
	-- ..表示字符串拼接
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtepch.h"
	-- 对于visual studio 还要指定pchsource cpp设置为create， .h设置为use
	pchsource "MyTinyEngine/src/mtepch.cpp"

	-- files 表示项目中包含的文件
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	-- includedirs 表示项目中包含的头文件
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	-- filter 表示过滤器，可以根据不同的配置进行不同的设置
	filter "system:windows"
		cppdialect "C++17"
		-- 	Sets <RuntimeLibrary> to "MultiThreaded"
		staticruntime "On"
		systemversion "latest"

		-- 定义宏
		defines
		{
			"MTE_PLATFORM_WINDOWS",
			"MTE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- postbuildcommands 表示在编译后执行的命令
		postbuildcommands
		{
			-- 将编译后的dll 复制到Sandbox中
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "MT_DEBUG"
		-- buildoptions 表示编译选项 /MDd 表示使用多线程调试库 multithreaded dll debug
		buildoptions "/MDd"
		-- symbols 表示是否生成调试信息
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		-- '/MD' 表示使用多线程库 multithreaded dll '
		buildoptions "/MD"
		-- optimize 表示是否优化
		optimize "On"

	filter "configurations:Dist"
		defines "MT_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MyTinyEngine/vendor/spdlog/include",
		"MyTinyEngine/src"
	}

	-- link a list of library and project names. 类似与CMAKE中的target_link_libraries
	links
	{
		"MyTinyEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MTE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MT_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MT_DIST"
		buildoptions "/MD"
		optimize "On"