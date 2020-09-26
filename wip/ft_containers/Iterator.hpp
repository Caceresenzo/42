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

namespace ft
{
	template<class It>
		typename std::iterator_traits<It>::difference_type
		do_distance(It first, It last, std::input_iterator_tag)
		{
			typename std::iterator_traits<It>::difference_type result = 0;

			while (first != last)
			{
				++first;
				++result;
			}

			return (result);
		}

	template<class It>
		typename std::iterator_traits<It>::difference_type
		do_distance(It first, It last, std::random_access_iterator_tag)
		{
			return (last - first);
		}

	template<class It>
		typename std::iterator_traits<It>::difference_type
		distance(It first, It last)
		{
			return do_distance(first, last, typename std::iterator_traits<It>::iterator_category());
		}

	template<typename T>
		class BaseIterator
		{
			private:
				BaseIterator();

			protected:
				T *_ptr;

			public:
				BaseIterator(T *ptr) :
						_ptr(ptr)
				{
				}

				BaseIterator(const BaseIterator &other) :
						_ptr(other._ptr)
				{
				}

				virtual
				~BaseIterator()
				{
				}

				bool
				operator==(const BaseIterator &rhs) const
				{
					return (_ptr == rhs._ptr);
				}

				bool
				operator!=(const BaseIterator &rhs) const
				{
					return (_ptr != rhs._ptr);
				}

				bool
				operator<(const BaseIterator &rhs) const
				{
					return (_ptr < rhs._ptr);
				}

				bool
				operator>(const BaseIterator &rhs) const
				{
					return (_ptr > rhs._ptr);
				}

				bool
				operator<=(const BaseIterator &rhs) const
				{
					return (_ptr <= rhs._ptr);
				}

				bool
				operator>=(const BaseIterator &rhs) const
				{
					return (_ptr >= rhs._ptr);
				}

				T*
				base() const
				{
					return (_ptr);
				}
		};

	template<typename T>
		class BaseConstIterator
		{
			private:
				BaseConstIterator();

			protected:
				const T *_ptr;

			public:
				BaseConstIterator(const T *ptr) :
						_ptr(ptr)
				{
				}

				BaseConstIterator(const BaseConstIterator &other) :
						_ptr(other._ptr)
				{
				}

				BaseConstIterator(const BaseIterator<T> &other) :
						_ptr(other._ptr)
				{
				}

				virtual
				~BaseConstIterator()
				{
				}

				bool
				operator==(const BaseConstIterator &rhs) const
				{
					return (_ptr == rhs._ptr);
				}

				bool
				operator!=(const BaseConstIterator &rhs) const
				{
					return (_ptr != rhs._ptr);
				}

				bool
				operator<(const BaseConstIterator &rhs) const
				{
					return (_ptr < rhs._ptr);
				}

				bool
				operator>(const BaseConstIterator &rhs) const
				{
					return (_ptr > rhs._ptr);
				}

				bool
				operator<=(const BaseConstIterator &rhs) const
				{
					return (_ptr <= rhs._ptr);
				}

				bool
				operator>=(const BaseConstIterator &rhs) const
				{
					return (_ptr >= rhs._ptr);
				}

				const T*
				base() const
				{
					return (_ptr);
				}
		};
}

#endif /* ITERATOR_HPP_ */
