#pragma once

#include "Sea/Common/CommonType.hpp"

namespace Sea
{

	template<typename T>
	struct Vector2
	{

	public:
		T x, y;

	public:
		Vector2(T x, T y);
		~Vector2()=default;
		
		float Length() const;
		float Dot(Vector2<T> vec) const;
		Vector2<T>& Normalize() const;

		Vector2<T> operator-() const;
		Vector2<T> operator-(const Vector2& vec) const;
		Vector2<T> operator*(const Vector2<T>& vec) const;
		Vector2<T> operator/(const Vector2& vec) const;
		Vector2<T> operator/(T scale) const;
		Vector2<T>& operator+=(const Vector2& vec);
		Vector2<T>& operator*=(const Vector2& vec);
		Vector2<T>& operator*=(T scale);
		Vector2<T>& operator/=(const Vector2& vec);
		Vector2<T>& operator/=(T scale);
		const Vector2<T>& operator+() const;
		bool operator==(const Vector2& vec) const;
		bool operator!=(const Vector2& vec) const;
		bool operator<(const Vector2& vec) const;
		bool operator<=(const Vector2& vec) const;
		bool operator>(const Vector2& vec) const;
		bool operator>=(const Vector2& vec) const;

	};

	using Vector2b = Vector2<bool>;
	using Vector2f = Vector2<f32>;
	using Vector2d = Vector2<f64>;
	using Vector2i = Vector2<std::int32_t>;
	using Vector2ui = Vector2<std::uint32_t>;
	using Vector2ll = Vector2<std::int64_t>;
	using Vector2ull = Vector2<std::uint64_t>;

	template<typename T> std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec);
}



#include "Sea/Math/Vector2.inl"
