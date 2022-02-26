/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:05:57 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/23 15:05:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
# define VECTOR_HPP_

# include <cmath>
# include <cassert>

template<typename T>
	struct Vector2
	{
		public:
			T x;
			T y;

		public:
			Vector2(const T &initial = T()) :
					x(initial),
					y(initial)
			{
			}

			Vector2(const T &x, const T &y) :
					x(x),
					y(y)
			{
			}

			Vector2(const Vector2<T> &other) :
					x(other.x),
					y(other.y)
			{
			}

			void
			zero()
			{
				T value = T();

				x = value;
				y = value;
			}
	};

template<typename T>
	struct Vector3
	{
		public:
			T x;
			T y;
			T z;

		public:
			Vector3(const T &initial = T()) :
					x(initial),
					y(initial),
					z(initial)
			{
			}

			Vector3(const T &x, const T &y, const T &z) :
					x(x),
					y(y),
					z(z)
			{
			}

			Vector3(const Vector3<T> &other) :
					x(other.x),
					y(other.y),
					z(other.z)
			{
			}

			Vector3
			operator-() const
			{
				return (Vector3(-x, -y, -z));
			}

			Vector3
			operator-(const Vector3 &right) const
			{
				return (Vector3(x - right->x, y - right->y, z - right->z));
			}

			Vector3
			operator*(const T &factor) const
			{
				return (Vector3(x * factor, y * factor, z * factor));
			}

			Vector3
			operator/(const T &factor) const
			{
				return (Vector3(x / factor, y / factor, z / factor));
			}

			T
			length_squared() const
			{
				return ((x * x) + (y * y) + (z * z));
			}

			T
			dot(const Vector3 &right) const
			{
				return ((x * right->x) + (y * right->y) + (z * right->z));
			}

			void
			normalize()
			{
				float square = this->length_squared();

				if (square == 0)
					return (zero());

				T length = std::sqrt(square);
				x /= length;
				y /= length;
				z /= length;
			}

			Vector3
			cross(const Vector3 &right) const
			{
				T x = (this->y * right->z) - (this->z * right->y);
				T y = (this->z * right->x) - (this->x * right->z);
				T z = (this->x * right->y) - (this->y * right->x);

				return (Vector3(x, y, z));
			}

			void
			zero()
			{
				T value = T();

				x = value;
				y = value;
				z = value;
			}
	};

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;

#endif /* VECTOR_HPP_ */
