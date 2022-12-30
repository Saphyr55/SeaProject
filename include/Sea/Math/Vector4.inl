#include "Sea/Math/Vector4.hpp"

#include <cmath>
#include <ostream>

namespace Sea
{

	template<typename T>
	inline Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }

	template<typename T>
	inline Vector4<T>::Vector4() : Vector4(0,0,0,0) { }

	template<typename T>
	inline Vector4<T>::Vector4(Vector3<T> vec, T w) : Vector4(vec.x, vec.y, vec.z, w) { }

	template<typename T>
	inline Vector4<T>::Vector4(Vector4<T>& vec) : Vector4(vec.x, vec.y, vec.z, vec.w) { }

	template<typename T>
	inline Vector4<T>::Vector4(const Vector4<T>& vec) : Vector4(vec.x, vec.y, vec.z, vec.w) { }

	template<typename T>
	inline float Vector4<T>::Length()
	{
		return Sqrt(Abs(x * x + y * y + z * z + w * w));
	}

	template<typename T>
	inline float Vector4<T>::Dot(Vector4<T> vec)
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::Normalize()
	{
		T norm = Length();
		x /= norm;
		y /= norm;
		z /= norm;
		w /= norm;
		return *this;
	}

	template<typename T>
	inline const Vector4<T> Vector4<T>::Cross(const Vector4 vec) const
	{
		return Vector4<T>
		(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x,
			1
		);
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Cross(Vector4 vec)
	{
		return Vector4<T>
		(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x,
			1
		);
	}

	template<typename T>
	inline Array<T, 4>& Vector4<T>::ToArray()
	{
		Array<T, 4> a{ x, y, z, w };
		return a;
	}

	template<typename T>
	const Vector4<T>& Vector4<T>::operator+() const
	{
		return *this;
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator+(const Vector4& vec) const
	{
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-(const Vector4& vec) const
	{
		return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator*(const Vector4& vec) const
	{
		return Vector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator/(const Vector4& vec) const
	{
		return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator/(T scale) const
	{
		return Vector4(x / scale, y / scale, z / scale, w / scale);
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator+=(const Vector4& vec) 
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator*=(const Vector4& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator*=(T scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator/=(const Vector4& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;

		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator/=(T scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		w /= scale;

		return *this;
	}

	template<typename T>
	bool Vector4<T>::operator==(const Vector4& vec) const
	{
		return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
	}

	template<typename T>
	bool Vector4<T>::operator!=(const Vector4& vec) const
	{
		return !operator==(vec);
	}

	template<typename T>
	bool Vector4<T>::operator<=(const Vector4& vec) const
	{
		if (x == (T)vec.x)
		{
			if (y == (T)vec.y)
				return z == (T)vec.z || z <= (T)vec.z;
			
			return y < (T)vec.y;
		}
		
		return x <= (T)vec.x;
	}

	template<typename T>
	bool Vector4<T>::operator<(const Vector4& vec) const
	{
		if (x == (T)vec.x)
		{
			if (y == (T)vec.y)
				return z == (T)vec.z || z < (T)vec.z;
			
			return y < (T)vec.y;
		}
		
		return x < (T)vec.x;
	}

	template<typename T>
	bool Vector4<T>::operator>(const Vector4& vec) const
	{
		return !operator<=(vec);
	}

	template<typename T>
	bool Vector4<T>::operator>=(const Vector4& vec) const
	{
		return !operator<(vec);
	}


	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Vector4<T>& vec)
	{
		return out << "Vector4(" << vec.x << ", " << vec.y << ')';
	}
}
