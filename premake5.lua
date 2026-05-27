workspace "PhanesEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PhanesEngine"
	location "PhanesEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		buildoptions { "/utf-8" }

		defines 
		{ 
			"PN_PLATFORMS_WINDOWS", 
			"PN_BUILD_DLL" 
		}

		postbuildcommands
		{
			"{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game/",
		}
		
	filter "configurations:Debug"
		defines "PN_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"PhanesEngine/vendor/spdlog/include",
		"PhanesEngine/src",
	}

	links
	{
		"PhanesEngine"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		buildoptions { "/utf-8" }

		defines
		{
			"PN_PLATFORMS_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		optimize "On"