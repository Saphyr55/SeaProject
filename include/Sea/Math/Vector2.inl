#include "Sea/Math/Vector2.hpp"

#include <cmath>
#include <ostream>

#include "Sea/Math/Math.hpp"

namespace Sea
{
	template<typename T>
	inline Vector2<T>::Vector2(T x, T y) : x(x) , y(y) { }

	template<typename T>
	inline float Vector2<T>::Length() const
	{
		return Sqrt(x * x + y * y);
	}

	template<typename T>
	inline float Vector2<T>::Dot(Vector2<T> vec) const
	{
		return x * vec.x + y * vec.y;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::Normalize() const
	{
		T norm = Length();
		x /= norm;
		y /= norm;
		return *this;
	}

	template<typename T>
	const Vector2<T>& Vector2<T>::operator+() const
	{
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2(-x, -y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(const Vector2& vec) const
	{
		return Vector2(x * vec.x, y * vec.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(const Vector2& vec) const
	{
		return Vector2(x / vec.x, y / vec.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(T scale) const
	{
		return Vector2(x / scale, y / scale);
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator*=(const Vector2& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator*=(T scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator/=(const Vector2& vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator/=(T scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
	
	template<typename T>
	bool Vector2<T>::operator==(const Vector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	template<typename T>
	bool Vector2<T>::operator!=(const Vector2& vec) const
	{
		return !operator==(vec);
	}

	template<typename T>
	bool Vector2<T>::operator<(const Vector2& vec) const
	{
		if (x == vec.x) return y < vec.y;
		return x < vec.x;
	}

	template<typename T>
	bool Vector2<T>::operator<=(const Vector2& vec) const
	{
		if (x == vec.x) return y <= vec.y;
		return x <= vec.x;
	}

	template<typename T>
	bool Vector2<T>::operator>(const Vector2& vec) const
	{
		return !operator<=(vec);
	}

	template<typename T>
	bool Vector2<T>::operator>=(const Vector2& vec) const
	{
		return !operator<(vec);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec)
	{
		return out << "Vector2(" << vec.x << ", " << vec.y << ')';
	}
}
