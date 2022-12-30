#pragma once

#include "Sea/Common/CommonType.hpp"

namespace Sea
{

	template<typename T>
	struct Vector4
	{

	public:
		T x, y, z, w;

	public:

		Vector4();
		Vector4(Vector4<T>& vec);
		Vector4(const Vector4<T>& vec);
		Vector4(T x, T y, T z, T w);
		~Vector4() = default;

		T Length();
		T Dot(Vector4<T> vec);
		Vector4<T>& Normalize();
		const Vector4<T> Cross(const Vector4 vec) const;
		Vector4<T> Cross(Vector4 vec);
		Array<T, 4>& ToArray();

		Vector4<T> operator-() const;
		Vector4<T> operator+(const Vector4& vec) const;
		Vector4<T> operator-(const Vector4& vec) const;
		Vector4<T> operator*(const Vector4<T>& vec) const;
		Vector4<T> operator/(const Vector4& vec) const;
		Vector4<T> operator/(T scale) const;
		Vector4<T>& operator+=(const Vector4& vec);
		Vector4<T>& operator*=(const Vector4& vec);
		Vector4<T>& operator*=(T scale);
		Vector4<T>& operator/=(const Vector4& vec);
		Vector4<T>& operator/=(T scale);
		const Vector4<T>& operator+() const;
		bool operator==(const Vector4& vec) const;
		bool operator!=(const Vector4& vec) const;
		bool operator<(const Vector4& vec) const;
		bool operator<=(const Vector4& vec) const;
		bool operator>(const Vector4& vec) const;
		bool operator>=(const Vector4& vec) const;

	};

	using Vector4b = Vector4<bool>;
	using Vector4f = Vector4<f32>;
    using Vector4d = Vector4<f64>;
	using Vector4i = Vector4<std::int32_t>;
	using Vector4ui = Vector4<std::uint32_t>;
	using Vector4ll = Vector4<std::int64_t>;
	using Vector4ull = Vector4<std::uint64_t>;

	template<typename T> std::ostream& operator<<(std::ostream& out, const Vector4<T>&vec);


}

#include "Sea/Math/Vector4.inl"
