#include "Sea/Math/Matrix4.hpp"
#include "Sea/Math/Vector4.hpp"

#include <iostream>

namespace Sea
{
	template<typename T>
	Matrix4<T>::Matrix4()
	{
		SetZero();
	}

	template<typename T>
	Matrix4<T>::Matrix4
	(
		T m11, T m21, T m31, T m41,
		T m12, T m22, T m32, T m42,
		T m13, T m23, T m33, T m43,
		T m14, T m24, T m34, T m44
	) : 
		m_vec1(Vector4<T>(m11, m12, m13, m14)),
		m_vec2(Vector4<T>(m21, m22, m23, m24)),
		m_vec3(Vector4<T>(m31, m32, m33, m34)),
		m_vec4(Vector4<T>(m41, m42, m43, m44))
	{						 
	}						 

	template<typename T>
	Matrix4<T>::Matrix4(Vector4<T> col_1, Vector4<T> col_2, Vector4<T> col_3, Vector4<T> col_4) 
		: m_vec1(col_1), m_vec2(col_2), m_vec3(col_3), m_vec4(col_4) 
	{ 

	}

	template<typename T>
	Vector4<T>& Matrix4<T>::GetCol(u32 index)
	{
		switch (index)
		{
		case 0:
			return m_vec1;
		case 1:
			return m_vec2;
		case 2:
			return m_vec3;
		case 3:
			return m_vec4;
		default:
			throw std::exception("Max 4");
		}
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::SetZero()
	{
		m_vec1 = Vector4<T>();
		m_vec2 = Vector4<T>();
		m_vec3 = Vector4<T>();
		m_vec4 = Vector4<T>();
		return *this;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::SetIdentity()
	{
		m_vec1 = Vector4<T>(T(1), T(0), T(0), T(0));
		m_vec2 = Vector4<T>(T(0), T(1), T(0), T(0));
		m_vec3 = Vector4<T>(T(0), T(0), T(1), T(0));
		m_vec4 = Vector4<T>(T(0), T(0), T(0), T(1));
		return *this;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::Transform(const Vector3<T>& v)
	{
		Matrix4<T> r(Vector4f((*this)[0]), Vector4f((*this)[1]), Vector4f((*this)[2]), Vector4f((*this)[3]));
		r[3] = Vector4f((*this)[0]) * v.x + Vector4f((*this)[1]) * v.y + Vector4f((*this)[2]) * v.z + Vector4f((*this)[3]);
		return r;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::operator*(Matrix4& m)
	{
		auto r = MakeRef<Matrix4<T>>();
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				 (*r)[i][j] =
					m[i][0] * (*this)[0][j] +
					m[i][1] * (*this)[1][j] +
					m[i][2] * (*this)[2][j] +
					m[i][3] * (*this)[3][j];
			}
		}
		return *r;
	}

	template<typename T>
	Vector4<T>& Matrix4<T>::operator[](std::size_t i)
	{
		return GetCol(i);
	}

	template<typename T>
	T& Matrix4<T>::operator()(std::size_t m, std::size_t n)
	{
		return GetCol(m)[n];
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::Identity()
	{
		return Matrix4<T>().SetIdentity();
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::Zero()
	{
		return Matrix4<T>().SetZero();
	}

	template<typename T>
	bool Matrix4<T>::operator==(const Matrix4& mat) const
	{
		return m_vec1 == mat.m_vec1 && m_vec2 == mat.m_vec2 && m_vec3 == mat.m_vec3 && m_vec4 == mat.m_vec4;
	}

	template<typename T>
	bool Matrix4<T>::operator!=(const Matrix4& mat) const
	{
		return !operator==(mat);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, Matrix4<T>& mat)
	{
		out << "Matrix4(" << "\n";
		out << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << " " << mat[3][0] << "\n";
		out << mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << " " << mat[3][1] << "\n";
		out << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << " " << mat[3][2] << "\n";
		out << mat[0][3] << " " << mat[1][3] << " " << mat[2][3] << " " << mat[3][3] << "\n";
		out << ")" << "\n";
		return out;
	}


}

