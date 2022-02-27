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
//
//			void
//			look_at(Vector3<T> eye, Vector3<T> center, Vector3<T> up)
//			{
//				Vector3<T> f, s, u;
//
//				f = eye - center;
//				f.normalize();
//
//				s = f.cross(up);
//				f.normalize();
//
//				u = s.cross(f);
//
//				identity();
//
//				storage[0][0] = s.x;
//				storage[1][0] = s.y;
//				storage[2][0] = s.z;
//				storage[0][1] = u.x;
//				storage[1][1] = u.y;
//				storage[2][1] = u.z;
//				storage[0][2] = -f.x;
//				storage[1][2] = -f.y;
//				storage[2][2] = -f.z;
//				storage[3][0] = -s.dot(eye);
//				storage[3][1] = -u.dot(eye);
//				storage[3][2] = f.dot(eye);
//			}
//
//			void
//			perspective(float fov, float aspect, float zNear, float zFar)
//			{
//				const float tanHalfFovy = tan(fov / 2.0f);
//
//				zero();
//
//				storage[0][0] = (1.0f) / (aspect * tanHalfFovy);
//				storage[1][1] = (1.0f) / (tanHalfFovy);
//				storage[2][2] = -(zFar + zNear) / (zFar - zNear);
//				storage[2][3] = -(1.0f);
//				storage[3][2] = -((2.0f) * zFar * zNear) / (zFar - zNear);
//			}
	};

template<int R1, int C1, int C2, typename T>
	Matrix<R1, C2, T>
	operator*(const Matrix<R1, C1, T> &lhs, const Matrix<C1, C2, T> &rhs)
	{
		Matrix<R1, C2, T> result;

		for (int i = R1; i--;)
			for (int j = C2; j--;)
				result[i][j] = lhs[i] * rhs.col(j);

		return result;
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
	rotate(const Matrix<4, 4, T> &source, const T &angle, const Vector<3, T> &vector)
	{
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);

		Vector<3, T> axis(::normalize(vector));
		Vector<3, T> temp(axis * (T(1) - c));

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

#endif /* MATRIX_HPP_ */
