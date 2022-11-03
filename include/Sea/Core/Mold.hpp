#pragma once

#include <type_traits>

#include <mcl/Logger.hpp>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Context.hpp"
#include "Sea/Backend/OpenGL/GLTexture.hpp"
#include "Sea/Backend/OpenGL/GLMesh.hpp"
#include "Sea/Backend/OpenGL/GLShader.hpp"

using mcl::Log;

namespace Sea
{	

	struct Molder
	{
		static GraphicsAPI api;

		template<typename Base, typename T>
		inline static constexpr bool is_same()
		{
			return std::is_same<Base, T>::value;
		}
	};

	template<typename T, typename ...Args>
	Mold<T> Mould(Args&& ...args)
	{
		switch (Molder::api)
		{
		case GraphicsAPI::OpenGL:

			if constexpr (std::is_same_v<T, Texture>)
				return std::make_shared<Backend::OpenGL::GLTexture>(std::forward<Args>(args)...);

			if constexpr (std::is_same_v<T, Mesh>)
				return std::make_shared<Backend::OpenGL::GLMesh>(std::forward<Args>(args)...);

			if constexpr (std::is_same_v<T, Shader>)
				return std::make_shared<Backend::OpenGL::GLShader>(std::forward<Args>(args)...);

		default:
			break;
		}

		throw std::exception("Mould() can only take contextual class");
	}

}