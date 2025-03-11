workspace "vertex-forge"
    configurations { "Debug", "Release" }
    architecture "x64"

    outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"
    vendordir = "%{prj.name}/vendor"

    project "vertex-forge"
        kind "ConsoleApp"
        language "C++"
        location "vertex-forge"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        includedirs { 
            (vendordir .. "/glew/include"), 
            (vendordir .. "/glfw/include"),
            (vendordir .. "/imgui/imgui"),
            (vendordir .. "/imgui/imgui/backends"),
            (vendordir .. "/stb")
        }

        libdirs { 
            (vendordir .. "/glew/lib"),
            (vendordir .. "/glfw/lib") }

        links { 
            "glfw3", 
            "glew32s" }

        files { 
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
            (vendordir .. "/imgui/imgui/*.cpp"),
            (vendordir .. "/imgui/imgui/*.h"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_glfw.cpp"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_glfw.h"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_opengl3.cpp"),
            (vendordir .. "/imgui/imgui/backends/imgui_impl_opengl3.h")
        }

        vpaths {
            ["Headers/*"] = "vertex-forge/src/**.h",
            ["Sources/*"] = {"vertex-forge/src/**.cpp"},
            ["Vendor/Headers"] = {"vertex-forge/vendor/**.h"},
            ["Vendor/Sources"] = {"vertex-forge/vendor/**.cpp"}
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
