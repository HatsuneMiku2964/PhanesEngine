workspace "PhanesEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist", }
    platforms { "x64" }
    startproject "Game"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "PhanesEngine/vendor/GLFW/include"
IncludeDirs["Glad"] = "PhanesEngine/vendor/Glad/include"
IncludeDirs["ImGui"] = "PhanesEngine/vendor/imgui"
IncludeDirs["glm"] = "PhanesEngine/vendor/glm"

group "Dependencies"
    include "PhanesEngine/vendor/GLFW"
    include "PhanesEngine/vendor/Glad"
    include "PhanesEngine/vendor/imgui"

group ""


project "PhanesEngine"
    location "PhanesEngine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pnpch.h"
    pchsource "PhanesEngine/src/pnpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }
    
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.glm}",
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }
    
    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        
        buildoptions { "/utf-8" }
        
        defines 
        { 
            "PN_PLATFORMS_WINDOWS",
            "PN_BUILD_DLL",
            "PN_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE",
        }

        postbuildcommands
        {
            ("{COPYFILE} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\""),
        }
        
    filter "configurations:Debug"
        defines "PN_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "PN_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "PN_DIST"
        runtime "Release"
        optimize "On"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDirs.glm}",
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
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "PN_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "PN_DIST"
        runtime "Release"
        optimize "On"