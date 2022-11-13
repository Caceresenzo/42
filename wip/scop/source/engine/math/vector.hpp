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

#include <lang/IllegalArgumentException.hpp>
#include <lang/Math.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <typeinfo>

template<int N, typename T>
	struct Vector
	{
		public:
			typedef T value_type;

		public:
			static const int SIZE = N;

		public:
			T data[N];
	};

template<typename T>
	struct Vector<2, T>
	{
		public:
			typedef T value_type;

		public:
			static const int SIZE = 2;
			static const Vector ZERO;

		public:
			T x;
			T y;

		public:
			Vector(const T &initial = T()) :
				x(initial),
				y(initial)
			{
			}

			Vector(const T &x, const T &y) :
				x(x),
				y(y)
			{
			}

			Vector(const Vector &other) :
				x(other.x),
				y(other.y)
			{
			}

			~Vector()
			{
			}

			inline Vector<2, T>&
			operator=(const Vector<2, T> &right)
			{
				x = right.x;
				y = right.y;

				return (*this);
			}

			inline T&
			operator[](int index)
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				throw IllegalArgumentException("vector<3>: out of bound");
			}

			inline const T&
			operator[](int index) const
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				throw IllegalArgumentException("vector<3>: out of bound");
			}
	};

template<typename T>
	struct Vector<3, T>
	{
		public:
			typedef T value_type;

		public:
			static const int SIZE = 3;
			static const Vector ZERO;
			static const Vector ONE;

		public:
			T x;
			T y;
			T z;

		public:
			Vector(const T &initial = T()) :
				x(initial),
				y(initial),
				z(initial)
			{
			}

			Vector(const T &x, const T &y, const T &z) :
				x(x),
				y(y),
				z(z)
			{
			}

			Vector(const Vector &other) :
				x(other.x),
				y(other.y),
				z(other.z)
			{
			}

			~Vector()
			{
			}

			inline Vector<3, T>&
			operator=(const Vector<3, T> &right)
			{
				x = right.x;
				y = right.y;
				z = right.z;

				return (*this);
			}

			inline Vector<3, T>&
			operator+=(const Vector<3, T> &right)
			{
				x += right.x;
				y += right.y;
				z += right.z;

				return (*this);
			}

			inline Vector<3, T>&
			operator-=(const Vector<3, T> &right)
			{
				x -= right.x;
				y -= right.y;
				z -= right.z;

				return (*this);
			}

			inline T&
			operator[](int index)
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				if (index == 2)
					return (z);

				throw IllegalArgumentException("vector<3>: out of bound");
			}

			inline const T&
			operator[](int index) const
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				if (index == 2)
					return (z);

				throw IllegalArgumentException("vector<3>: out of bound");
			}
	};

template<typename T>
	struct Vector<4, T>
	{
		public:
			typedef T value_type;

		public:
			static const int SIZE = 4;
			static const Vector ZERO;

		public:
			T x;
			T y;
			T z;
			T w;

		public:
			Vector(const T &initial = T()) :
				x(initial),
				y(initial),
				z(initial),
				w(initial)
			{
			}

			Vector(const T &x, const T &y, const T &z, const T &w) :
				x(x),
				y(y),
				z(z),
				w(w)
			{
			}

			Vector(const Vector &other) :
				x(other.x),
				y(other.y),
				z(other.z),
				w(other.w)
			{
			}

			~Vector()
			{
			}

			inline Vector<4, T>&
			operator=(const Vector<4, T> &right)
			{
				x = right.x;
				y = right.y;
				z = right.z;
				w = right.w;

				return (*this);
			}

			inline T&
			operator[](int index)
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				if (index == 2)
					return (z);

				if (index == 3)
					return (w);

				std::cout << index << std::endl << std::flush;

				throw IllegalArgumentException("vector<4>: out of bound");
			}

			inline const T&
			operator[](int index) const
			{
				if (index == 0)
					return (x);

				if (index == 1)
					return (y);

				if (index == 2)
					return (z);

				if (index == 3)
					return (w);

				std::cout << index << std::endl << std::flush;

				throw IllegalArgumentException("vector<4>: out of bound");
			}
	};

template<int N, typename T>
	inline Vector<N, T>
	operator-(const Vector<N, T> &left)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = -left[i];

		return (vector);
	}

template<int N, typename T>
	inline Vector<N, T>
	operator-(const Vector<N, T> &left, const Vector<N, T> &right)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = left[i] - right[i];

		return (vector);
	}

template<int N, typename T>
	inline Vector<N, T>
	operator+(const Vector<N, T> &left, const Vector<N, T> &right)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = left[i] + right[i];

		return (vector);
	}

template<int N, typename T, typename U>
	inline Vector<N, T>
	operator*(const Vector<N, T> &left, const U &right)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = left[i] * right;

		return (vector);
	}

template<int N, typename T>
	inline Vector<N, T>
	operator/(const Vector<N, T> &left, const T &right)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = left[i] / right;

		return (vector);
	}

template<int N, typename T>
	inline T
	length_squared(const Vector<N, T> &input)
	{
		T squared = T();

		for (int i = 0; i < N; ++i)
		{
			const T &value = input[i];
			squared += value * value;
		}

		return (squared);
	}

template<int N, typename T>
	inline T
	length(const Vector<N, T> &input)
	{
		return (Math::sqrt(length_squared(input)));
	}

template<int N, typename T>
	inline T
	dot(const Vector<N, T> &left, const Vector<N, T> &right)
	{
		T value = T();

		for (int i = 0; i < N; ++i)
			value += left[i] * right[i];

		return (value);
	}

template<int N, typename T>
	inline Vector<N, T>
	normalize(const Vector<N, T> &input)
	{
		float length = ::length(input);

		if (length == 0)
			return (Vector<N, T>(0));

		return (input / length);
	}

template<int N, typename T>
	inline Vector<N, T>
	abs(const Vector<N, T> &input)
	{
		Vector<N, T> vector;

		for (int i = 0; i < N; ++i)
			vector[i] = Math::abs(input[i]);

		return (vector);
	}

template<typename T>
	inline Vector<3, T>
	cross(const Vector<3, T> &right, const Vector<3, T> &left)
	{
		T x = (right.y * left.z) - (right.z * left.y);
		T y = (right.z * left.x) - (right.x * left.z);
		T z = (right.x * left.y) - (right.y * left.x);

		return (Vector<3, T>(x, y, z));
	}

template<int N, typename T>
	inline bool
	operator==(const Vector<N, T> &left, const Vector<N, T> &right)
	{
		for (int i = N; i--;)
			if (left[i] != right[i])
				return (false);

		return (true);
	}

template<int N, typename T>
	inline bool
	operator!=(const Vector<N, T> &left, const Vector<N, T> &right)
	{
		return (!(left == right));
	}

template<int N, typename T>
	inline std::ostream&
	operator<<(std::ostream &stream, const Vector<N, T> &vector)
	{
		stream << "Vector<" << N << ", " << typeid(T).name() << ">(";

		for (int i = 0; i < N; ++i)
		{
			stream << vector[i];

			if (i != N - 1)
				stream << ", ";
		}

		return (stream << ");");
	}

#endif /* VECTOR_HPP_ */
