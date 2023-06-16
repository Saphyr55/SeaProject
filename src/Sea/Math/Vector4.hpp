#pragma once

#include <cmath>
#include <ostream>

#include "Sea/Core/Common.hpp"

namespace Sea
{
	template<typename T>
	class Vector3;

	template<typename T>
	class Vector4
	{

	public:
		T x, y, z, w;

	public:

		Vector4();
		Vector4(T x, T y, T z, T w);
		Vector4(Vector4<T>& vec);
		Vector4(const Vector4<T>& vec);
		Vector4(Vector3<T> vec, T w);
		~Vector4() = default;

		float Length();
		float Dot(Vector4<T> vec);
		Vector4<T>& Normalize();
		const Vector4<T> Cross(const Vector4 vec) const;
		Vector4<T> Cross(Vector4 vec);
		Array<T, 4>& ToArray();

		Vector4<T> operator-() const;
		Vector4<T> operator+(const Vector4& vec) const;
		Vector4<T> operator-(const Vector4& vec) const;
		Vector4<T> operator*(const Vector4<T>& vec) const;
		Vector4<T> operator/(const Vector4& vec) const;
		Vector4<T> operator*(T scale) const;
		Vector4<T> operator/(T scale) const;
		Vector4<T>& operator-=(const Vector4& vec);
		Vector4<T>& operator+=(const Vector4& vec);
		Vector4<T>& operator*=(const Vector4& vec);
		Vector4<T>& operator*=(T scale);
		Vector4<T>& operator/=(const Vector4& vec);
		Vector4<T>& operator/=(T scale);
		T& operator[](std::size_t i);
		const Vector4<T>& operator+() const;
		bool operator==(const Vector4& vec) const;
		bool operator!=(const Vector4& vec) const;
		bool operator<(const Vector4& vec) const;
		bool operator<=(const Vector4& vec) const;
		bool operator>(const Vector4& vec) const;
		bool operator>=(const Vector4& vec) const;

	};

	typedef Vector4<bool> Vector4b;
	typedef Vector4<f32> Vector4f;
	typedef Vector4<f64> Vector4d;
	typedef Vector4<std::int32_t> Vector4i;
	typedef Vector4<std::uint32_t> Vector4ui;
	typedef Vector4<std::int64_t> Vector4ll;
	typedef Vector4<std::uint64_t> Vector4ull;

	template<typename T> 
	std::ostream& operator<<(std::ostream& out, const Vector4<T>&vec);


}

#include "Sea/Math/Vector4.inl"
 
