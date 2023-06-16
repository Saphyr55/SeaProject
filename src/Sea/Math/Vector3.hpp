#pragma once

#include "Sea/Core/Common.hpp"

namespace Sea
{

	template<typename T>
	class Vector3
	{

	public:
		T x, y, z;

	public:
		Vector3() = default;
		Vector3(T x, T y, T z);
		~Vector3() = default;

		float Length();
		float Dot(Vector3<T> vec);
		Vector3<T>& Normalize();
		const Vector3<T> Cross(const Vector3 vec) const;
		Vector3<T> Cross(Vector3 vec);

		Vector3<T> operator-() const;
		Vector3<T> operator+(const Vector3& vec) const;
		Vector3<T> operator-(const Vector3& vec) const;
		Vector3<T> operator*(T scale) const;
		Vector3<T> operator*(const Vector3<T>& vec) const;
		Vector3<T> operator/(const Vector3& vec) const;
		Vector3<T> operator/(T scale) const;

		Vector3<T>& operator+=(const Vector3& vec);
		Vector3<T>& operator-=(const Vector3& vec);
		Vector3<T>& operator*=(const Vector3& vec);
		Vector3<T>& operator*=(T scale);
		Vector3<T>& operator/=(const Vector3& vec);
		Vector3<T>& operator/=(T scale);

		bool operator==(const Vector3& vec) const;
		bool operator!=(const Vector3& vec) const;
		bool operator<(const Vector3& vec) const;
		bool operator<=(const Vector3& vec) const;
		bool operator>(const Vector3& vec) const;
		bool operator>=(const Vector3& vec) const;

	};

	using Vector3b = Vector3<bool>;
	using Vector3f = Vector3<f32>;
	using Vector3d = Vector3<f64>;
	using Vector3i = Vector3<std::int32_t>;
	using Vector3ui = Vector3<std::uint32_t>;
	using Vector3ll = Vector3<std::int64_t>;
	using Vector3ull = Vector3<std::uint64_t>;

}

#include "Sea/Math/Vector3.inl"
