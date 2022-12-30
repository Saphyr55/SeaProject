#pragma once

#include "Sea/Common/CommonType.hpp"
#include "Sea/Math/Vector4.hpp"

namespace Sea
{
    template<typename T>
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(Vector4<T> col_1, Vector4<T> col_2, Vector4<T> col_3, Vector4<T> col_4);

		Vector4<T>& GetCol(u32 index);
		Matrix4<T>& SetZero();
		Matrix4<T>& SetIdentity();

		Matrix4<T>& operator*(Matrix4& matrix);
		Array<T, 4>& operator[](std::size_t i);

	private:
		Vector4<T> m_col_1;
		Vector4<T> m_col_2;
		Vector4<T> m_col_3;
		Vector4<T> m_col_4;
	};

	using Matrix4f = Matrix4<f32>;
	using Matrix4d = Matrix4<f64>;

	template<typename T>
	std::ostream& operator<<(std::ostream& out, Matrix4<T>& mat);
}

#include "Sea/Math/Matrix4.inl"
