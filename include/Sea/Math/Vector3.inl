#include "Sea/Math/Vector3.hpp"
#include "Sea/Math/Math.hpp"

#include <cmath>
#include <ostream>

namespace Sea
{
	template<typename T>
	inline Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) { }

	template<typename T>
	inline T Vector3<T>::Length()
	{
		return Sqrt(Abs(x * x + y * y + z * z));
	}

	template<typename T>
	inline T Vector3<T>::Dot(Vector3<T> vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::Normalize()
	{
		T norm = Length();
		x /= norm;
		y /= norm;
		z /= norm;

		return *this;
	}

	template<typename T>
	inline const Vector3<T> Vector3<T>::Cross(const Vector3 vec) const
	{
		return Vector3<T>
		(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(Vector3 vec)
	{
		return Vector3<T>
		(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		);
	}

	template<typename T>
	const Vector3<T>& Vector3<T>::operator+() const
	{
		return *this;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3& vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*(const Vector3& vec) const
	{
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(const Vector3& vec) const
	{
		return Vector3(x / vec.x, y / vec.y, z / vec.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(T scale) const
	{
		return Vector3(x / scale, y / scale, , z / scale);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(const Vector3& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(T scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(const Vector3& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(T scale)
	{
		x /= scale;
		y /= scale;
		z /= vec.z;
		return *this;
	}

	template<typename T>
	bool Vector3<T>::operator==(const Vector3& vec) const
	{
		return x == vec.x && y == vec.y && z == vec.z;
	}
	 
	template<typename T>
	bool Vector3<T>::operator!=(const Vector3& vec) const
	{
		return !operator==(vec);
	}

	template<typename T>
	bool Vector3<T>::operator<=(const Vector3& vec) const
	{
		if (x == (T) vec.x)
		{
			if (y == (T) vec.y)
				return z == (T) vec.z || z <= (T)vec.z;
			else
				return y < (T)vec.y;
		}
		else
			return x <= (T)vec.x;
	}

	template<typename T>
	bool Vector3<T>::operator<(const Vector3& vec) const
	{
		if (x == (T)vec.x)
		{
			if (y == (T)vec.y)
				return z == (T)vec.z || z < (T)vec.z;
			else
				return y < (T)vec.y;
		}
		else
			return x < (T)vec.x;
	}

	template<typename T>
	bool Vector3<T>::operator>(const Vector3& vec) const
	{
		return !operator<=(vec);
	}

	template<typename T>
	bool Vector3<T>::operator>=(const Vector3& vec) const
	{
		return !operator<(vec);
	}


	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Vector3<T>& vec)
	{
		return out << "Vector3(" << vec.x << ", " << vec.y << ')';
	}
}
