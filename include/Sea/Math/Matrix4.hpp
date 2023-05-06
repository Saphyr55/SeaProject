#pragma once

#include "Sea/Common/CommonType.hpp"

namespace Sea
{
	template<typename T>
	class Vector4;
	template<typename T>
	class Vector3;

    template<typename T>
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(
			T m11, T m21, T m31, T m41,
			T m12, T m22, T m32, T m42, 
			T m13, T m23, T m33, T m43,
			T m14, T m24, T m34, T m44);
		Matrix4(Vector4<T> col_1, Vector4<T> col_2, Vector4<T> col_3, Vector4<T> col_4);

		Vector4<T>& GetCol(u32 index);
		Matrix4<T>& SetZero();
		Matrix4<T>& SetIdentity();

		Matrix4<T>& operator*(Matrix4& matrix);
		Vector4<T>& operator[](std::size_t i);
		T& operator()(std::size_t m, std::size_t n);
		bool operator==(const Matrix4& mat) const;
		bool operator!=(const Matrix4& mat) const;

		Matrix4<T>& Transform(const Vector3<T>& v);

		static Matrix4<T> Identity();
		static Matrix4<T> Zero();
		
	private:
		Vector4<T> m_vec1;
		Vector4<T> m_vec2;
		Vector4<T> m_vec3;
		Vector4<T> m_vec4;
	};

	using Matrix4f = Matrix4<f32>;
	using Matrix4d = Matrix4<f64>;

	template<typename T>
	std::ostream& operator<<(std::ostream& out, Matrix4<T>& mat);
}

#include "Sea/Math/Matrix4.inl"
