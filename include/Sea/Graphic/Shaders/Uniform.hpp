#pragma once

#include "Sea/Core/Common.hpp"
#include "Sea/Graphic/Rendering/Renderer.hpp"
#include "Sea/Graphic/Shaders/Shader.hpp"
#include "Sea/Math/Math.hpp"

#define SEA_GENERATE_UNIFORM(CName, Typename) using CName = Uniform<Typename>;

namespace Sea
{   
    
    template<typename T>
    class Uniform
    {

    public:
        inline Shader& Owner() const { return m_owner; }
        inline s32 Location() const { return m_location; }
        inline std::string Name() const { return m_name; }
		inline std::shared_ptr<T> Value() const { return m_value; }
        void Update();
        void Value(const std::shared_ptr<T> value);

    public:
        Uniform(Shader& owner, Renderer& renderer, std::string_view name, s32 location);

    protected:
        std::shared_ptr<T> m_value;
        bool m_has_changed = true;
        std::string m_name;
        Shader& m_owner;
        Renderer& m_renderer;
        s32 m_location;
    };

	SEA_GENERATE_UNIFORM(UniformBool, bool)
	SEA_GENERATE_UNIFORM(UniformF32, f32)
	SEA_GENERATE_UNIFORM(UniformS32, f32)
	SEA_GENERATE_UNIFORM(UniformVector3f, Vector3f)
	SEA_GENERATE_UNIFORM(UniformVector2f, Vector2f)
	SEA_GENERATE_UNIFORM(UniformVector4f, Vector4f)
	SEA_GENERATE_UNIFORM(UniformMatrix4f, Matrix4f)

    template<typename T>
    void Uniform<T>::Update()
    {
		if (!m_has_changed) return;
        m_has_changed = false;
    }

    template<typename T>
    void Uniform<T>::Value(const std::shared_ptr<T> value)
    {
        if (value == m_value)
            return;
        m_value = value;
        m_has_changed = true;
    }

    template<typename T>
    Uniform<T>::Uniform(Shader& owner, Renderer& renderer, std::string_view name, s32 location)
        : m_owner(owner), m_renderer(renderer), m_name(name), m_location(location)
    {
    }

}

#undef SEA_GENERATE_CLASS_UNIFORM