-- workspace ��ʾһ�������������԰��������Ŀ
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

-- include premake file ��λ�� copy from glfw premake5.lua
include "MyTinyEngine/vendor/GLFW"

-- project ��ʾһ����Ŀ�����԰�������ļ�
project "MyTinyEngine"
	-- location ��ʾ��Ŀ��λ�� vcxproj����λ��
	location "MyTinyEngine"
	-- dll
	kind "SharedLib"
	language "C++"
	-- ..��ʾ�ַ���ƴ��
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtepch.h"
	-- ����visual studio ��Ҫָ��pchsource cpp����Ϊcreate�� .h����Ϊuse
	pchsource "MyTinyEngine/src/mtepch.cpp"

	-- files ��ʾ��Ŀ�а������ļ�
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	-- includedirs ��ʾ��Ŀ�а�����ͷ�ļ�
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	-- filter ��ʾ�����������Ը��ݲ�ͬ�����ý��в�ͬ������
	filter "system:windows"
		cppdialect "C++17"
		-- 	Sets <RuntimeLibrary> to "MultiThreaded"
		staticruntime "On"
		systemversion "latest"

		-- �����
		defines
		{
			"MTE_PLATFORM_WINDOWS",
			"MTE_BUILD_DLL"
		}

		-- postbuildcommands ��ʾ�ڱ����ִ�е�����
		postbuildcommands
		{
			-- ��������dll ���Ƶ�Sandbox��
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "MT_DEBUG"
		-- symbols ��ʾ�Ƿ����ɵ�����Ϣ
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		-- optimize ��ʾ�Ƿ��Ż�
		optimize "On"

	filter "configurations:Dist"
		defines "MT_DIST"
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

	-- link a list of library and project names. ������CMAKE�е�target_link_libraries
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
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MT_DIST"
		optimize "On"