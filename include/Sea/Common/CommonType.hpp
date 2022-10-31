#pragma once

#include <memory>
#include <cstdint>

namespace Sea {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	using u8 = std::uint8_t;   ///< 8-bit unsigned byte
	using u16 = std::uint16_t; ///< 16-bit unsigned short
	using u32 = std::uint32_t; ///< 32-bit unsigned word
	using u64 = std::uint64_t; ///< 64-bit unsigned int

	using s8 = std::int8_t;   ///< 8-bit signed byte
	using s16 = std::int16_t; ///< 16-bit signed short
	using s32 = std::int32_t; ///< 32-bit signed word
	using s64 = std::int64_t; ///< 64-bit signed int

	using f32 = float;  ///< 32-bit floating point
	using f64 = double; ///< 64-bit floating point

}

