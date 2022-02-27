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

template<typename T>
	struct Matrix44
	{
		public:
			T storage[4][4];

			Matrix44(const T &initial = T()) :
					storage()
			{
				set(initial);
			}

			Matrix44&
			operator=(const Matrix44 &right)
			{
				if (this != &right)
				{
					for (int i = 0; i < 4; ++i)
						for (int j = 0; j < 4; ++j)
							this->storage[i][j] = right.storage[i][j];
				}

				return (*this);
			}

			Matrix44
			operator*(const Matrix44 &right) const
			{
				assert(this != &right);

				Matrix44 result;

				result.storage[0][0] = this->storage[0][0] * right.storage[0][0] + this->storage[0][1] * right.storage[1][0] + this->storage[0][2] * right.storage[2][0] + this->storage[0][3] * right.storage[3][0];
				result.storage[0][1] = this->storage[0][0] * right.storage[0][1] + this->storage[0][1] * right.storage[1][1] + this->storage[0][2] * right.storage[2][1] + this->storage[0][3] * right.storage[3][1];
				result.storage[0][2] = this->storage[0][0] * right.storage[0][2] + this->storage[0][1] * right.storage[1][2] + this->storage[0][2] * right.storage[2][2] + this->storage[0][3] * right.storage[3][2];
				result.storage[0][3] = this->storage[0][0] * right.storage[0][3] + this->storage[0][1] * right.storage[1][3] + this->storage[0][2] * right.storage[2][3] + this->storage[0][3] * right.storage[3][3];
				result.storage[1][0] = this->storage[1][0] * right.storage[0][0] + this->storage[1][1] * right.storage[1][0] + this->storage[1][2] * right.storage[2][0] + this->storage[1][3] * right.storage[3][0];
				result.storage[1][1] = this->storage[1][0] * right.storage[0][1] + this->storage[1][1] * right.storage[1][1] + this->storage[1][2] * right.storage[2][1] + this->storage[1][3] * right.storage[3][1];
				result.storage[1][2] = this->storage[1][0] * right.storage[0][2] + this->storage[1][1] * right.storage[1][2] + this->storage[1][2] * right.storage[2][2] + this->storage[1][3] * right.storage[3][2];
				result.storage[1][3] = this->storage[1][0] * right.storage[0][3] + this->storage[1][1] * right.storage[1][3] + this->storage[1][2] * right.storage[2][3] + this->storage[1][3] * right.storage[3][3];
				result.storage[2][0] = this->storage[2][0] * right.storage[0][0] + this->storage[2][1] * right.storage[1][0] + this->storage[2][2] * right.storage[2][0] + this->storage[2][3] * right.storage[3][0];
				result.storage[2][1] = this->storage[2][0] * right.storage[0][1] + this->storage[2][1] * right.storage[1][1] + this->storage[2][2] * right.storage[2][1] + this->storage[2][3] * right.storage[3][1];
				result.storage[2][2] = this->storage[2][0] * right.storage[0][2] + this->storage[2][1] * right.storage[1][2] + this->storage[2][2] * right.storage[2][2] + this->storage[2][3] * right.storage[3][2];
				result.storage[2][3] = this->storage[2][0] * right.storage[0][3] + this->storage[2][1] * right.storage[1][3] + this->storage[2][2] * right.storage[2][3] + this->storage[2][3] * right.storage[3][3];
				result.storage[3][0] = this->storage[3][0] * right.storage[0][0] + this->storage[3][1] * right.storage[1][0] + this->storage[3][2] * right.storage[2][0] + this->storage[3][3] * right.storage[3][0];
				result.storage[3][1] = this->storage[3][0] * right.storage[0][1] + this->storage[3][1] * right.storage[1][1] + this->storage[3][2] * right.storage[2][1] + this->storage[3][3] * right.storage[3][1];
				result.storage[3][2] = this->storage[3][0] * right.storage[0][2] + this->storage[3][1] * right.storage[1][2] + this->storage[3][2] * right.storage[2][2] + this->storage[3][3] * right.storage[3][2];
				result.storage[3][3] = this->storage[3][0] * right.storage[0][3] + this->storage[3][1] * right.storage[1][3] + this->storage[3][2] * right.storage[2][3] + this->storage[3][3] * right.storage[3][3];

				return (result);
			}

			void
			translate(const Vector3<T> &vector)
			{
				storage[3][0] += storage[0][0] * vector.x + storage[1][0] * vector.y + storage[2][0] * vector.z;
				storage[3][1] += storage[0][1] * vector.x + storage[1][1] * vector.y + storage[2][1] * vector.z;
				storage[3][2] += storage[0][2] * vector.x + storage[1][2] * vector.y + storage[2][2] * vector.z;
				storage[3][3] += storage[0][3] * vector.x + storage[1][3] * vector.y + storage[2][3] * vector.z;
			}

			void
			rotate(float angle, const Vector3<T> &vector)
			{
				const float a = angle;
				const float c = std::cos(a);
				const float s = std::sin(a);

				Vector3<T> axis(vector);
				axis.normalize();

				Matrix44 result;

				result.storage[0][0] = c + ((1.0f) - c) * axis.x * axis.x;
				result.storage[0][1] = ((1.0f) - c) * axis.x * axis.y + s * axis.z;
				result.storage[0][2] = ((1.0f) - c) * axis.x * axis.z - s * axis.y;
				result.storage[0][3] = (0.0f);

				result.storage[1][0] = ((1.0f) - c) * axis.y * axis.x - s * axis.z;
				result.storage[1][1] = c + ((1.0f) - c) * axis.y * axis.y;
				result.storage[1][2] = ((1.0f) - c) * axis.y * axis.z + s * axis.x;
				result.storage[1][3] = (0.0f);

				result.storage[2][0] = ((1.0f) - c) * axis.z * axis.x + s * axis.y;
				result.storage[2][1] = ((1.0f) - c) * axis.z * axis.y - s * axis.x;
				result.storage[2][2] = c + ((1.0f) - c) * axis.z * axis.z;
				result.storage[2][3] = (0.0f);

				result.storage[3][0] = 0.0f;
				result.storage[3][1] = 0.0f;
				result.storage[3][2] = 0.0f;
				result.storage[3][3] = 1.0f;

				*this = *this * result;
			}

			void
			scale(const Vector3<T> &vector)
			{
				T x = vector.x;
				T y = vector.y;
				T z = vector.z;

				storage[0][0] *= x;
				storage[0][1] *= x;
				storage[0][2] *= x;
				storage[0][3] *= x;

				storage[1][0] *= y;
				storage[1][1] *= y;
				storage[1][2] *= y;
				storage[1][3] *= y;

				storage[2][0] *= z;
				storage[2][1] *= z;
				storage[2][2] *= z;
				storage[2][3] *= z;
			}

			void
			look_at(Vector3<T> eye, Vector3<T> center, Vector3<T> up)
			{
				Vector3<T> f, s, u;

				f = eye - center;
				f.normalize();

				s = f.cross(up);
				f.normalize();

				u = s.cross(f);

				identity();

				storage[0][0] = s.x;
				storage[1][0] = s.y;
				storage[2][0] = s.z;
				storage[0][1] = u.x;
				storage[1][1] = u.y;
				storage[2][1] = u.z;
				storage[0][2] = -f.x;
				storage[1][2] = -f.y;
				storage[2][2] = -f.z;
				storage[3][0] = -s.dot(eye);
				storage[3][1] = -u.dot(eye);
				storage[3][2] = f.dot(eye);
			}

			void
			perspective(float fov, float aspect, float zNear, float zFar)
			{
				const float tanHalfFovy = tan(fov / 2.0f);

				zero();

				storage[0][0] = (1.0f) / (aspect * tanHalfFovy);
				storage[1][1] = (1.0f) / (tanHalfFovy);
				storage[2][2] = -(zFar + zNear) / (zFar - zNear);
				storage[2][3] = -(1.0f);
				storage[3][2] = -((2.0f) * zFar * zNear) / (zFar - zNear);
			}

			void
			set(const T &value)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						storage[i][j] = value;
			}

			void
			zero()
			{
				set(T());
			}

			Matrix44
			identity()
			{
				Matrix44 matrix;

				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						storage[i][j] = T(i == j);

				return (matrix);
			}

			void
			print()
			{
				printf("m4f { %8.4f, %8.4f, %8.4f, %8.4f,\n"
					"      %8.4f, %8.4f, %8.4f, %8.4f,\n"
					"      %8.4f, %8.4f, %8.4f, %8.4f,\n"
					"      %8.4f, %8.4f, %8.4f, %8.4f}\n", //
				storage[0][0], storage[0][1], storage[0][2], storage[0][3], //
				storage[1][0], storage[1][1], storage[1][2], storage[1][3], //
				storage[2][0], storage[2][1], storage[2][2], storage[2][3], //
				storage[3][0], storage[3][1], storage[3][2], storage[3][3]);
			}
	};

#endif /* MATRIX_HPP_ */
