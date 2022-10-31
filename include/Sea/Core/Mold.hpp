#pragma once

#include <type_traits>

#include <mcl/Logger.hpp>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/GLMesh.hpp"
#include "Sea/Backend/OpenGL/GLShader.hpp"
#include "Sea/Backend/OpenGL/GLTexture.hpp"

using mcl::Log;

using namespace Sea::Backend::OpenGL;

namespace Sea
{	
	template<typename T>
	using Mold = std::shared_ptr<T>;

	template<typename T, typename ...Args>
	Mold<T> Mould(Args&& ...args);

	struct Molder
	{
		static ContextType context;

		template<typename Base, typename T>
		inline static constexpr bool is_same()
		{
			return std::is_same<Base, T>::value;
		}
	};

	template<typename T, typename ...Args>
	Mold<T> Mould(Args&& ...args)
	{
		switch (Molder::context)
		{
		case Sea::ContextType::OpenGL:

			if constexpr (std::is_same_v<T, Texture>)
				return std::make_shared<GLTexture>(std::forward<Args>(args)...);

			if constexpr (std::is_same_v<T, Mesh>)
				return std::make_shared<GLMesh>(std::forward<Args>(args)...);

			if constexpr (std::is_same_v<T, Shader>)
				return std::make_shared<GLShader>(std::forward<Args>(args)...);

		default:
			break;
		}

		throw std::exception("Molder can only take contextual class");
	}

}