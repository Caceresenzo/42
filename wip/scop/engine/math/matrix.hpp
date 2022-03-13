/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:02:26 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/23 15:02:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP_
# define MATRIX_HPP_

#include <engine/math/Math.hpp>
#include <engine/math/vector.hpp>
#include <cassert>
#include <cmath>
#include <cstdio>

template<int R, int C, typename T>
	struct Matrix
	{
		public:
			Vector<C, T> rows[R];

			Matrix(const T &initial = T()) :
					rows()
			{
				for (int i = 0; i < R; ++i)
					for (int j = 0; j < C; ++j)
						rows[i][j] = i == j ? initial : T(0);
			}

			Matrix(const Matrix &other)
			{
				for (int i = 0; i < R; ++i)
					rows[i] = other.rows[i];
			}

			Vector<C, T>&
			operator[](const int index)
			{
				assert(index >= 0 && index < R);
				return (rows[index]);
			}

			const Vector<C, T>&
			operator[](const int index) const
			{
				assert(index >= 0 && index < R);
				return (rows[index]);
			}

			Matrix&
			operator=(const Matrix &right)
			{
				if (this != &right)
				{
					for (int i = R; i--;)
						rows[i] = right.rows[i];
				}

				return (*this);
			}

			Vector<R, T>
			col(const int index) const
			{
				assert(index >= 0 && index < C);

				Vector<R, T> vector;

				for (int i = R; i--;)
					vector[i] = rows[i][vector];

				return (vector);
			}

			void
			set_col(const int index, const Vector<R, T> &col)
			{
				assert(index >= 0 && index < C);

				Vector<R, T> vector;

				for (int i = R; i--;)
					rows[i][index] = col[i];
			}
	};

template<typename T>
	inline Matrix<4, 4, T>
	operator*(const Matrix<4, 4, T> &left, const Matrix<4, 4, T> &right)
	{
		Matrix<4, 4, T> result;

		for (int k = 0; k < 4; ++k)
			for (int j = 0; j < 4; ++j)
				result[k][j] = left[0][j] * right[k][0] + left[1][j] * right[k][1] + left[2][j] * right[k][2] + left[3][j] * right[k][3];

		return (result);
	}

template<int R, int C, typename T>
	inline bool
	operator==(const Matrix<R, C, T> &left, const Matrix<R, C, T> &right)
	{
		for (int i = R; i--;)
			if (left[i] != right[i])
				return (false);

		return (true);
	}

template<int R, int C, typename T>
	inline bool
	operator!=(const Matrix<R, C, T> &left, const Matrix<R, C, T> &right)
	{
		return (!(left == right));
	}

template<typename T>
	inline Matrix<4, 4, T>
	translate(const Matrix<4, 4, T> &source, const Vector<3, T> &vector)
	{
		Matrix<4, 4, T> matrix(source);

		matrix[3] = source[0] * vector[0] + source[1] * vector[1] + source[2] * vector[2] + source[3];

		return (matrix);
	}

template<typename T>
	inline Matrix<4, 4, T>
	scale(const Matrix<4, 4, T> &source, const Vector<3, T> &vector)
	{
		Matrix<4, 4, T> matrix(source);

		matrix[0] = source[0] * vector[0];
		matrix[1] = source[1] * vector[1];
		matrix[2] = source[2] * vector[2];
		matrix[3] = source[3];

		return (matrix);
	}

template<typename T>
	inline Matrix<4, 4, T>
	rotate(const Matrix<4, 4, T> &source, const Vector<3, T> &vector)
	{
		T const a = 1;
		T const c = cos(a);
		T const s = sin(a);

		Vector<3, float> axis = ::normalize(vector);
		Vector<3, T> temp = axis * (T(1) - c);

		Matrix<4, 4, T> rotate;
		rotate[0][0] = c + temp[0] * axis[0];
		rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		rotate[1][1] = c + temp[1] * axis[1];
		rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		rotate[2][2] = c + temp[2] * axis[2];

		Matrix<4, 4, T> matrix(source);
		matrix[0] = source[0] * rotate[0][0] + source[1] * rotate[0][1] + source[2] * rotate[0][2];
		matrix[1] = source[0] * rotate[1][0] + source[1] * rotate[1][1] + source[2] * rotate[1][2];
		matrix[2] = source[0] * rotate[2][0] + source[1] * rotate[2][1] + source[2] * rotate[2][2];
		matrix[3] = source[3];

		return (matrix);
	}

template<typename T>
	inline Matrix<4, 4, T>
	rotate(const Matrix<4, 4, T> &source, const T &angle, const Vector<3, float> &vector)
	{
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);

		Vector<3, float> axis = ::normalize(vector);
		Vector<3, T> temp = axis * (T(1) - c);

		Matrix<4, 4, T> rotate;
		rotate[0][0] = c + temp[0] * axis[0];
		rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		rotate[1][1] = c + temp[1] * axis[1];
		rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		rotate[2][2] = c + temp[2] * axis[2];

		Matrix<4, 4, T> matrix(source);
		matrix[0] = source[0] * rotate[0][0] + source[1] * rotate[0][1] + source[2] * rotate[0][2];
		matrix[1] = source[0] * rotate[1][0] + source[1] * rotate[1][1] + source[2] * rotate[1][2];
		matrix[2] = source[0] * rotate[2][0] + source[1] * rotate[2][1] + source[2] * rotate[2][2];
		matrix[3] = source[3];

		return (matrix);
	}

template<typename T>
	inline Matrix<4, 4, T>
	look_at(const Vector<3, T> &eye, const Vector<3, T> &center, const Vector<3, T> &up)
	{
		Vector<3, T> const f(::normalize(center - eye));
		Vector<3, T> const s(::normalize(::cross(f, up)));
		Vector<3, T> const u(::cross(s, f));

		Matrix<4, 4, T> matrix(1);
		matrix[0][0] = s.x;
		matrix[1][0] = s.y;
		matrix[2][0] = s.z;
		matrix[0][1] = u.x;
		matrix[1][1] = u.y;
		matrix[2][1] = u.z;
		matrix[0][2] = -f.x;
		matrix[1][2] = -f.y;
		matrix[2][2] = -f.z;
		matrix[3][0] = -dot(s, eye);
		matrix[3][1] = -dot(u, eye);
		matrix[3][2] = dot(f, eye);

		return (matrix);
	}

template<typename T>
	inline Matrix<4, 4, T>
	perspective(const T &fov, const T &aspect, const T &zNear, const T &zFar)
	{
		const float tanHalfFovy = Math::tan(fov / static_cast<T>(2));

		Matrix<4, 4, T> matrix;
		matrix[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		matrix[1][1] = static_cast<T>(1) / (tanHalfFovy);
		matrix[2][2] = -(zFar + zNear) / (zFar - zNear);
		matrix[2][3] = -static_cast<T>(1);
		matrix[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);

		return (matrix);
	}

template<int R, int C, typename T>
	inline std::ostream&
	operator<<(std::ostream &stream, const Matrix<R, C, T> &matrix)
	{
		stream << "Matrix<" << R << ", " << C << ", " << typeid(T).name() << ">(\n ";

		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
			{
				stream << matrix[j][i];
				stream << ", ";

				if (j == C - 1)
					stream << "\n ";
			}
		}

		return (stream << ");");
	}

#endif /* MATRIX_HPP_ */
