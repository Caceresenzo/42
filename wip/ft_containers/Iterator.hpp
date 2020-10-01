/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:27:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/25 17:27:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
# define ITERATOR_HPP_

# include <iterator>
# include <cstddef>
# include "TypeTraits.hpp"

namespace ft
{
	struct input_iterator_tag
	{
	};

	struct output_iterator_tag
	{
	};

	struct forward_iterator_tag :
			input_iterator_tag
	{
	};

	struct bidirectional_iterator_tag :
			forward_iterator_tag
	{
	};

	struct random_access_iterator_tag :
			bidirectional_iterator_tag
	{
	};

	template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
		struct iterator
		{
			public:
				typedef T value_type;
				typedef Distance difference_type;
				typedef Pointer pointer;
				typedef Reference reference;
				typedef Category iterator_category;
		};

	template<typename Iterator>
		struct iterator_traits
		{
			public:
				typedef typename Iterator::iterator_category iterator_category;
				typedef typename Iterator::value_type value_type;
				typedef typename Iterator::difference_type difference_type;
				typedef typename Iterator::pointer pointer;
				typedef typename Iterator::reference reference;
		};

	template<typename T>
		struct iterator_traits<T*>
		{
			public:
				typedef random_access_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T *pointer;
				typedef T &reference;
		};

	template<typename T>
		struct iterator_traits<const T*>
		{
			public:
				typedef random_access_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef const T *pointer;
				typedef const T &reference;
		};

	template<typename Iterator>
		Iterator
		next(Iterator iterator, unsigned long n = 1)
		{
			while (n--)
				++iterator;
			return (iterator);
		}

	template<class It>
		typename ft::iterator_traits<It>::difference_type
		do_distance(It first, It last, ft::input_iterator_tag)
		{
			typename ft::iterator_traits<It>::difference_type result = 0;

			while (first != last)
			{
				++first;
				++result;
			}

			return (result);
		}

	template<class It>
		typename ft::iterator_traits<It>::difference_type
		do_distance(It first, It last, ft::random_access_iterator_tag)
		{
			return (last - first);
		}

	template<class It>
		typename ft::iterator_traits<It>::difference_type
		distance(It first, It last)
		{
			return do_distance(first, last, typename ft::iterator_traits<It>::iterator_category());
		}

	template<class T>
		class normal_iterator :
				public ft::iterator<ft::random_access_iterator_tag, T>
		{
			private:
				typedef typename ft::iterator_traits<T> traits;

			public:
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::reference reference;
				typedef typename traits::pointer pointer;

			private:
				T _ptr;

			public:
				normal_iterator() :
						_ptr(NULL)
				{
				}

				explicit
				normal_iterator(const T &ptr) :
						_ptr(ptr)
				{
				}

				template<typename U>
					normal_iterator(const normal_iterator<U> &other) :
							_ptr(other.base())
					{
					}

				~normal_iterator()
				{
				}

				normal_iterator&
				operator=(const normal_iterator &rhs)
				{
					this->_ptr = rhs._ptr;

					return (*this);
				}

				normal_iterator&
				operator++()
				{
					this->_ptr++;

					return (*this);
				}

				normal_iterator
				operator++(int)
				{
					normal_iterator copy = *this;

					this->_ptr++;

					return (copy);
				}

				normal_iterator&
				operator--()
				{
					this->_ptr--;

					return (*this);
				}

				normal_iterator
				operator--(int)
				{
					normal_iterator copy = *this;

					this->_ptr--;

					return (copy);
				}

				normal_iterator&
				operator+=(difference_type n)
				{
					this->_ptr += n;

					return (*this);
				}

				normal_iterator
				operator+(difference_type n) const
				{
					return (normal_iterator(this->_ptr + n));
				}

				normal_iterator&
				operator-=(difference_type n)
				{
					this->_ptr -= n;

					return (*this);
				}

				normal_iterator
				operator-(difference_type n) const
				{
					return (normal_iterator(this->_ptr - n));
				}

				difference_type
				operator-(const normal_iterator &other)
				{
					return (this->_ptr - other.base());
				}

				reference
				operator*() const
				{
					return (*this->_ptr);
				}

				pointer
				operator->() const
				{
					return (this->_ptr);
				}

				reference
				operator[](difference_type n) const
				{
					return (*(this->_ptr + n));
				}

				const T&
				base() const
				{
					return (_ptr);
				}
		};

	template<typename T>
		inline bool
		operator==(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator==(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<typename T>
		inline bool
		operator!=(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator!=(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template<typename T>
		inline bool
		operator<(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator<(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template<typename T>
		inline bool
		operator>(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator>(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template<typename T>
		inline bool
		operator<=(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator<=(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template<typename T>
		inline bool
		operator>=(const normal_iterator<T> &lhs, const normal_iterator<T> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template<typename T, typename U>
		inline bool
		operator>=(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template<typename T>
		inline normal_iterator<T>
		operator+(typename normal_iterator<T>::difference_type n, const normal_iterator<T> &it)
		{
			return (normal_iterator<T>(it.base() + n));
		}

	template<typename T, typename U>
		inline typename normal_iterator<T>::difference_type
		operator-(const normal_iterator<T> &lhs, const normal_iterator<U> &rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template<class Iterator>
		class reverse_iterator :
				public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_traits<Iterator>::difference_type, typename ft::iterator_traits<Iterator>::pointer, typename ft::iterator_traits<Iterator>::reference>
		{
			private:
				typedef typename ft::iterator_traits<Iterator> traits;

			public:
				typedef Iterator iterator_type;
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::pointer pointer;
				typedef typename traits::reference reference;

			private:
				iterator_type _it;

			public:
				reverse_iterator()
				{
				}

				explicit
				reverse_iterator(iterator_type it) :
						_it(it)
				{
				}

				template<class Iter>
					reverse_iterator(const reverse_iterator<Iter> &rev_it) :
							_it(rev_it._it)
					{
					}

				iterator_type
				base() const
				{
					return (_it);
				}

				reference
				operator*() const
				{
					iterator_type copy = _it;
					return (*--copy);
				}

				reverse_iterator
				operator+(difference_type n) const
				{
					return (reverse_iterator(_it - n));
				}

				reverse_iterator&
				operator++()
				{
					--_it;

					return (*this);
				}

				reverse_iterator
				operator++(int)
				{
					reverse_iterator copy = *this;

					--_it;

					return (copy);
				}

				reverse_iterator&
				operator+=(difference_type n)
				{
					_it -= n;

					return (*this);
				}

				reverse_iterator
				operator-(difference_type n) const
				{
					return (reverse_iterator(_it + n));
				}

				reverse_iterator&
				operator--()
				{
					++_it;

					return (*this);
				}

				reverse_iterator
				operator--(int)
				{
					reverse_iterator copy = *this;

					++_it;

					return (copy);
				}

				reverse_iterator&
				operator-=(difference_type n)
				{
					_it += n;

					return (*this);
				}

				pointer
				operator->() const
				{
					return (&(operator*()));
				}

				/**
				 * Accesses the element located n positions away from the element currently pointed to by the iterator.
				 * If such an element does not exist, it causes undefined behavior.
				 * Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
				 *
				 * @param n Number of elements to offset.
				 * @return A reference to the element n positions away from the element currently pointed by the iterator.
				 */
				reference
				operator[](difference_type n) const
				{
					return (base()[-n - 1]);
				}
		};

	template<class Iterator>
		inline bool
		operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<class Iterator>
		inline bool
		operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (!(lhs == rhs));
		}

	template<class Iterator>
		inline bool
		operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (rhs.base() < lhs.base());
		}

	template<class Iterator>
		inline bool
		operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (!(rhs < lhs));
		}

	template<class Iterator>
		inline bool
		operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (rhs < lhs);
		}

	template<class Iterator>
		inline bool
		operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (!(lhs < rhs));
		}

	template<class Iterator>
		inline reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
		{
			return (reverse_iterator<Iterator>(rev_it.base() - n));
		}

	template<class Iterator>
		inline typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{
			return (rhs.base() - lhs.base());
		}
}

#endif /* ITERATOR_HPP_ */
