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

	-- files 表示项目中包含的文件
	files
	{
		"%{prj.name}/src/MTE/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- includedirs 表示项目中包含的头文件
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
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
			"MTE_BUILD_DLL"
		}

		-- postbuildcommands 表示在编译后执行的命令
		postbuildcommands
		{
			-- 将编译后的dll 复制到Sandbox中
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "MT_DEBUG"
		-- symbols 表示是否生成调试信息
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		-- optimize 表示是否优化
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
		symbols "On"

	filter "configurations:Release"
		defines "MT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MT_DIST"
		optimize "On"