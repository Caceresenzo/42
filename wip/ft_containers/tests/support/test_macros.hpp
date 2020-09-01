/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:08:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:08:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_MACROS_HPP_
# define TEST_MACROS_HPP_

# include <iostream>
# include <exception>

#define ASSERT(cond) \
		if (!(cond)) { \
			ASSERT_FAIL(cond); \
		}

#define ASSERT_EXCEPT(code) \
		try { \
			code; \
			ASSERT_FAIL(code); \
		} catch (...) { \
			ASSERT(true); \
		}

#define ASSERT_NOEXCEPT(code) \
		try { \
			code; \
			ASSERT(true); \
		} catch (...) { \
			ASSERT_FAIL(code); \
		}

#define ASSERT_FAIL(code) \
		std::cout << "assert failed " << __FILE__ << ":" << __LINE__ << " { " << #code << " }" << std::endl; \
		exit(1); \

#define ASSERT_AWARE_ZERO() ASSERT(aware_count == 0);

#define TEST_BLOCK(code) do \
	{ \
		code \
	} while (0);

#define TEST_AWARE_BLOCK(code) \
	TEST_BLOCK(code); \
	ASSERT_AWARE_ZERO();

template<class _Tp>
	inline _Tp*
	addressof(_Tp &__x)
	{
		return reinterpret_cast<_Tp*>(const_cast<char*>(&reinterpret_cast<const volatile char&>(__x)));
	}

static int aware_count = 0;

template<class T>
	class Aware
	{
		private:
			T _x;

		public:

			Aware() :
			        _x(0)
			{
				aware_count++;
			}

			Aware(T x) :
			        _x(x)
			{
				aware_count++;
			}

			Aware(const Aware &other) :
			        _x(other._x)
			{
				aware_count++;
			}

			~Aware()
			{
				aware_count--;
			}

			Aware&
			operator =(const Aware &right)
			{
				_x = right._x;

				return (*this);
			}

			bool
			operator ==(const Aware &right) const
			{
				return (_x == right._x);
			}

			T&
			x() const
			{
				return (_x);
			}
	};

#endif /* TEST_MACROS_HPP_ */
