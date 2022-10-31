local targetdir = "bin/$(plat)_$(arch)_$(mode)"
local version = "cxx20"
local project_name = "SeaProject"

add_requires("libsdl", "libsdl_image", "glm", "imgui")
add_rules("mode.release", "mode.debug")

set_project(project_name)
set_languages(version)

add_includedirs("include")
add_includedirs("externals")
set_targetdir(targetdir)

target("SeaFramework")
    set_kind("static")

    add_files("src/**.cpp")
    add_files("externals/**.c")
    add_files("externals/**.cpp")
    add_headerfiles("externals/mcl/Logger.hpp", { public = true } )
    add_headerfiles("include/**.hpp")
    add_headerfiles("externals/**.hpp")
    add_headerfiles("externals/**.h")

    add_packages("libsdl", "libsdl_image", "glm", "imgui", { public = true } )
target_end()

target("SeaExample")
    set_kind("binary")

    add_deps("SeaFramework")
    
    add_files("examples/**.cpp")
    add_headerfiles("examples/**.hpp")
target_end()

