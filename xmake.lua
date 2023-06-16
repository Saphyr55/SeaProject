local project_name = "SeaProject"
local version = "cxx20"
local targetdir = "bin/$(plat)_$(arch)_$(mode)"
local include_folder = "src/Sea/"
local src_folder = "src/Sea/"
local default_kind = "static"

local add_header_files_module = function (file) 
    add_headerfiles(include_folder .. file)
end 

local add_files_module = function (file) 
    add_files(src_folder .. file)
end 

local Modules = {

    --- Core Module ---
    Core = {
        Name = "Sea.Core",
        Packages = { "libsdl", "glm", "fmt", { public = true } },
        Handle = function ()
            add_header_files_module("Core/**.hpp")
            add_headerfiles("externals/**.h|**.hpp")
            add_files_module("Core/**.cpp")
            add_files("externals/**.c|**.cpp")
        end 
    },

    --- Graphic Module ---
    Graphics = {
        Name = "Sea.Graphics",
        Packages = { "assimp", "libsdl_image", { public = true } },
        Deps = { "Sea.Core", "Sea.Math" },
        Handle = function () 
            add_header_files_module("Graphics/**.hpp")
            add_files_module("Graphics/**.cpp")
        end
    },

    --- Input Module ---
    Input = {
        Name = "Sea.Input",
        Deps = { "Sea.Core", "Sea.Math" },
        Handle = function () 
            add_header_files_module("Input/**.hpp")
            add_files_module("Input/**.cpp")
        end
    },

    --- Math Module ---
    Math = {
        Name = "Sea.Math",
        Deps = { "Sea.Core" },
        Handle = function ()
            add_header_files_module("Math/**.hpp|**.inl")
        end
    },

    --- Ui Module ---
    Ui = {
        Name = "Sea.Ui",
        Deps = { "Sea.Core", "Sea.Math", "Sea.Graphics" },
        Handle = function () 
            add_header_files_module("Ui/**.hpp")
            add_files_module("Ui/**.cpp")
        end
    },

    --- Test Module ---
    Tests = {
        Name = "Sea.Tests",
        Kind = "binary",
        Packages = { "catch2" },
        Deps = { "Sea.Core", "Sea.Ui", "Sea.Input", "Sea.Math", "Sea.Graphics" },
        Handle = function () 
            add_files("tests/**.cpp")
        end
    },

    --- Sample Default Module ---
    SampleDefault = {
        Name = "Sea.Samples.Default",
        Kind = "binary",
        Deps = { "Sea.Core", "Sea.Ui", "Sea.Input", "Sea.Math", "Sea.Graphics" },
        Handle = function ()
            add_files("examples/sample_default/**.cpp")
        end
    },

    --- Sample Ui Module ---
    SampleUi = {
        Name = "Sea.Samples.Ui",
        Kind = "binary",
        Deps = { "Sea.Core", "Sea.Ui", "Sea.Input", "Sea.Math", "Sea.Graphics" },
        Handle = function ()
            add_files("examples/sample_ui/**.cpp")
        end
    },

}

local handle_modules = function (handler) 
    for _, module in pairs(Modules) do 
        handler(module)
    end
end

local on_exist = function (pr, on)
    if pr then 
        on()
    end
end

set_project(project_name)
set_languages(version)

add_requires("libsdl" , "libsdl_image", "glm", "fmt", "assimp", "catch2")

add_rules("mode.release", "mode.debug")

add_includedirs("src")
add_includedirs("externals")
set_targetdir(targetdir)

handle_modules(function (module)
    target(module.Name, function ()

        if module.Kind then 
            set_kind(module.Kind)
        else 
            set_kind(default_kind)
        end

        on_exist(module.Deps, function () 
            add_deps(unpack(module.Deps))
        end)
        
        on_exist(module.Handle, function () 
            module:Handle()
        end)

        on_exist(module.Packages, function () 
            add_packages(unpack(module.Packages))
        end)

    end)
end)