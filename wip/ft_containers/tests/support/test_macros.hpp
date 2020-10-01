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

# include "support_std.hpp"

# include <iostream>
# include <exception>
# include <memory>
# include <cstdlib>
# include <Iterator.hpp>

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

			const T&
			x() const
			{
				return (_x);
			}

			void
			x(std::string x)
			{
				_x = x;
			}
	};

template<typename T>
	class SimpleIterator :
			public ft::iterator<RANDOM_ACCESS_ITERATOR_TAG, T>
	{
		private:
			typedef typename ITERATOR_TRAITS<T> traits;

		public:
			typedef typename traits::iterator_category iterator_category;
			typedef typename traits::value_type value_type;
			typedef typename traits::difference_type difference_type;
			typedef typename traits::reference reference;
			typedef typename traits::pointer pointer;

		private:
			T _ptr;

		public:
			SimpleIterator() :
					_ptr(NULL)
			{
			}

			SimpleIterator(const T &ptr) :
					_ptr(ptr)
			{
			}

			virtual
			~SimpleIterator()
			{
			}

			SimpleIterator&
			operator++()
			{
				_ptr++;

				return (*this);
			}

			SimpleIterator
			operator++(int)
			{
				SimpleIterator cpy(_ptr);

				_ptr++;

				return (cpy);
			}

			SimpleIterator&
			operator--()
			{
				_ptr--;

				return (*this);
			}

			SimpleIterator
			operator--(int)
			{
				SimpleIterator cpy(_ptr);

				_ptr--;

				return (cpy);
			}

			reference
			operator*() const
			{
				return (*_ptr);
			}

			pointer
			operator->() const
			{
				return (_ptr);
			}

			bool
			operator==(const SimpleIterator &rhs) const
			{
				return (_ptr == rhs._ptr);
			}

			bool
			operator!=(const SimpleIterator &rhs) const
			{
				return (_ptr != rhs._ptr);
			}

			bool
			operator<(const SimpleIterator &rhs) const
			{
				return (_ptr < rhs._ptr);
			}

			bool
			operator>(const SimpleIterator &rhs) const
			{
				return (_ptr > rhs._ptr);
			}

			bool
			operator<=(const SimpleIterator &rhs) const
			{
				return (_ptr <= rhs._ptr);
			}

			bool
			operator>=(const SimpleIterator &rhs) const
			{
				return (_ptr >= rhs._ptr);
			}

			const pointer
			base() const
			{
				return (_ptr);
			}
	};

template<class T>
	typename SimpleIterator<T>::difference_type
	operator-(const SimpleIterator<T> &left, const SimpleIterator<T> &right)
	{
		return (left.base() - right.base());
	}

#endif /* TEST_MACROS_HPP_ */
