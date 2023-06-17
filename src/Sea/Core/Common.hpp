#pragma once

#include <utility>
#include <array>
#include <memory>
#include <cstdint>

namespace Sea 
{	

	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using s8 = std::int8_t;
	using s16 = std::int16_t;
	using s32 = std::int32_t;
	using s64 = std::int64_t;

	using f32 = float;
	using f64 = double;

	template<typename T, std::size_t size>
	using Array = std::array<T, size>;

	template<typename T> 
	using Ptr = std::unique_ptr<T>;

	template<typename T> 
	using Ref = std::shared_ptr<T>;

	template<typename T> 
	using Mold = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ptr<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> MakeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

