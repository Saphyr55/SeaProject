#include "Sea/Math/Matrix4.hpp"

namespace Sea
{
	template<typename T>
	inline Matrix4<T>::Matrix4()
	{
		SetZero();
	}

	template<typename T>
	inline Matrix4<T>::Matrix4(Vector4<T> col_1, Vector4<T> col_2, Vector4<T> col_3, Vector4<T> col_4) 
		: m_col_1(col_1), m_col_2(col_2), m_col_3(col_3), m_col_4(col_4) { }


	template<typename T>
	inline Vector4<T>& Matrix4<T>::GetCol(u32 index)
	{
		switch (index)
		{
		case 0:
			return m_col_1;
		case 1:
			return m_col_2;
		case 2:
			return m_col_3;
		case 3:
			return m_col_4;
		default:
			throw std::exception("Max 4");
		}
	}

	template<typename T>
	inline Matrix4<T>& Matrix4<T>::SetZero()
	{
		m_col_1 = Vector4<T>();
		m_col_2 = Vector4<T>();
		m_col_3 = Vector4<T>();
		m_col_4 = Vector4<T>();
		return *this;
	}

	template<typename T>
	inline Matrix4<T>& Matrix4<T>::SetIdentity()
	{
		m_col_1 = Vector4<T>(T(1), T(0), T(0), T(0));
		m_col_2 = Vector4<T>(T(0), T(1), T(0), T(0));
		m_col_3 = Vector4<T>(T(0), T(0), T(1), T(0));
		m_col_4 = Vector4<T>(T(0), T(0), T(0), T(1));
		return *this;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::operator*(Matrix4& m)
	{
		Matrix4<T> r;
		r.m_col_1 = Vector4<T>
		(
			T((*this)[0][0] * m[0][0] + (*this)[0][1] * m[1][0] + (*this)[0][2] * m[2][0] + (*this)[0][3] * m[3][0]),
			T((*this)[0][0] * m[0][1] + (*this)[0][1] * m[1][1] + (*this)[0][2] * m[2][1] + (*this)[0][3] * m[3][1]),
			T((*this)[0][0] * m[0][2] + (*this)[0][1] * m[1][2] + (*this)[0][2] * m[2][2] + (*this)[0][3] * m[3][2]),
			T((*this)[0][0] * m[0][3] + (*this)[0][1] * m[1][3] + (*this)[0][2] * m[2][3] + (*this)[0][3] * m[3][3])
		);
		r.m_col_2 = Vector4<T>
		(
			T((*this)[1][0] * m[0][0] + (*this)[1][1] * m[1][0] + (*this)[1][2] * m[2][0] + (*this)[1][3] * m[3][0]),
			T((*this)[1][0] * m[0][1] + (*this)[1][1] * m[1][1] + (*this)[1][2] * m[2][1] + (*this)[1][3] * m[3][1]),
			T((*this)[1][0] * m[0][2] + (*this)[1][1] * m[1][2] + (*this)[1][2] * m[2][2] + (*this)[1][3] * m[3][2]),
			T((*this)[1][0] * m[0][3] + (*this)[1][1] * m[1][3] + (*this)[1][2] * m[2][3] + (*this)[1][3] * m[3][3])
		);
		r.m_col_3 = Vector4<T>
		(
			T((*this)[2][0] * m[0][0] + (*this)[2][1] * m[1][0] + (*this)[2][2] * m[2][0] + (*this)[2][3] * m[3][0]),
			T((*this)[2][0] * m[0][1] + (*this)[2][1] * m[1][1] + (*this)[2][2] * m[2][1] + (*this)[2][3] * m[3][1]),
			T((*this)[2][0] * m[0][2] + (*this)[2][1] * m[1][2] + (*this)[2][2] * m[2][2] + (*this)[2][3] * m[3][2]),
			T((*this)[2][0] * m[0][3] + (*this)[2][1] * m[1][3] + (*this)[2][2] * m[2][3] + (*this)[2][3] * m[3][3])
		);
		r.m_col_4 = Vector4<T>
		(
			T((*this)[3][0] * m[0][0] + (*this)[3][1] * m[1][0] + (*this)[3][2] * m[2][0] + (*this)[3][3] * m[3][0]),
			T((*this)[3][0] * m[0][1] + (*this)[3][1] * m[1][1] + (*this)[3][2] * m[2][1] + (*this)[3][3] * m[3][1]),
			T((*this)[3][0] * m[0][2] + (*this)[3][1] * m[1][2] + (*this)[3][2] * m[2][2] + (*this)[3][3] * m[3][2]),
			T((*this)[3][0] * m[0][3] + (*this)[3][1] * m[1][3] + (*this)[3][2] * m[2][3] + (*this)[3][3] * m[3][3])
		);
		return r;
	}

	template<typename T>
	inline Array<T, 4>& Matrix4<T>::operator[](std::size_t i)
	{
		return GetCol(i).ToArray();
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, Matrix4<T>& mat)
	{
		Log::Info() << "Matrix4";
		Log::Info() << "(";
		Log::Info() << mat.GetCol(0).x << " " << mat.GetCol(1).x << " " << mat.GetCol(2).x << " " << mat.GetCol(3).x;
		Log::Info() << mat.GetCol(0).y << " " << mat.GetCol(1).y << " " << mat.GetCol(2).y << " " << mat.GetCol(3).y;
		Log::Info() << mat.GetCol(0).z << " " << mat.GetCol(1).z << " " << mat.GetCol(2).z << " " << mat.GetCol(3).z;
		Log::Info() << mat.GetCol(0).w << " " << mat.GetCol(1).w << " " << mat.GetCol(2).w << " " << mat.GetCol(3).w;
		Log::Info() << ")";
	}


}

