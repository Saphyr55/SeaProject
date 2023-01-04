#pragma once

#include <type_traits>

#include <mcl/Logger.hpp>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Context.hpp"

using mcl::Log;

namespace Sea
{	

	struct Molder
	{
		static GraphicsAPI API;

		template<typename Base, typename T>
		inline static constexpr bool is_same()
		{
			return std::is_same<Base, T>::value;
		}
	};

}