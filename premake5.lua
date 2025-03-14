workspace "Breakout"
    configurations { "Debug", "Release" }
    architecture "x64"

    startproject "game"

    outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"
    vendordir = "%{prj.name}/vendor"

    project "core"
        kind "StaticLib"
        language "C++"
        location "core"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        includedirs { 
            (vendordir .. "/glew/include"), 
            (vendordir .. "/glfw/include"),
            (vendordir .. "/imgui/imgui"),
            (vendordir .. "/imgui/imgui/backends"),
            (vendordir .. "/stb"),
            "%{prj.name}/include"
        }

        libdirs { 
            (vendordir .. "/glew/lib"),
            (vendordir .. "/glfw/lib") 
        }

        links { 
            "glfw3", 
            "glew32s" 
        }

        files { 
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/include/**.h",
            (vendordir .. "/imgui/imgui/*.cpp"),
            (vendordir .. "/imgui/imgui/*.h"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_glfw.cpp"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_glfw.h"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_opengl3.cpp"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_opengl3.h"),
        }

        vpaths {
            ["Headers/*"] = "core/include/**.h",
            ["Sources/*"] = "core/src/**.cpp",
            ["Vendor/Headers/*"] = {"core/vendor/**.h"},
            ["Vendor/Sources/*"] = {"core/vendor/**.cpp"}
         }

        filter "system:windows"
            cppdialect "C++20"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"


    project "game"
        kind "ConsoleApp"
        language "C++"
        location "game"

        outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        includedirs {
            "core/include"
        }    

        links "core"

        files { 
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
        }

        vpaths {
            ["Headers/*"] = {"game/src/**.h"},
            ["Sources/*"] = {"game/src/**.cpp"},
        }

        filter "system:windows"
            cppdialect "C++20"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"


