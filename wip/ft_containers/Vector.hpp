/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:36:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/25 14:36:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
# define VECTOR_HPP_

#include <Algorithm.hpp>
#include <Iterator.hpp>
#include <cstddef>
#include <limits>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace ft
{
	template<class U>
		class VectorIterator
		{
			private:
				typedef iterator_traits<U> traits;

			public:
				typedef U iterator_type;
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::pointer pointer;
				typedef typename traits::reference reference;

			private:
				iterator_type _value;

			public:

				VectorIterator()
				{
				}

				VectorIterator(iterator_type value) :
				        _value(value)
				{
				}

				template<class K>
					VectorIterator(const VectorIterator<K> &__u) :
					        _value(__u.base())
					{
					}

				reference
				operator*() const
				{
					return (*_value);
				}

				pointer
				operator->() const
				{
					return &(*_value);
				}

				VectorIterator&
				operator++()
				{
					++_value;

					return (*this);
				}

				VectorIterator
				operator++(int)
				{
					VectorIterator copy(*this);

					operator++();

					return (copy);
				}

				VectorIterator&
				operator--()
				{
					_value--;

					return (*this);
				}

				VectorIterator
				operator--(int)
				{
					VectorIterator copy(*this);

					operator--();

					return (copy);
				}

				VectorIterator
				operator+(difference_type n) const
				{
					VectorIterator copy(*this);

					copy += n;

					return (copy);
				}

				VectorIterator
				operator-(difference_type n) const
				{
					VectorIterator copy(*this);

					copy -= n;

					return (copy);
				}

				VectorIterator&
				operator+=(difference_type n)
				{
					_value += n;

					return (*this);
				}

				VectorIterator&
				operator-=(difference_type n)
				{
					_value -= n;

					return (*this);
				}

				reference
				operator[](difference_type n) const
				{
					return (_value[n]);
				}

				iterator_type
				base() const
				{
					return (_value);
				}

			private:

				template<class U1, class U2>
					friend
					bool
					operator==(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1, class U2>
					friend
					bool
					operator<(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1, class U2>
					friend
					bool
					operator!=(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1, class U2>
					friend
					bool
					operator>(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1, class U2>
					friend
					bool
					operator>=(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1, class U2>
					friend
					bool
					operator<=(const VectorIterator<U1> &x, const VectorIterator<U2>&);

				template<class U1>
					friend typename VectorIterator<U1>::difference_type
					operator+(typename VectorIterator<U1>::difference_type, VectorIterator<U1>);

				template<class U1, class U2>
					friend typename VectorIterator<U1>::difference_type
					operator-(const VectorIterator<U1> &x, const VectorIterator<U2>&);
		};

	template<class U>
		bool
		operator==(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() == right.base());
		}

	template<class U>
		bool
		operator!=(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() != right.base());
		}

	template<class U>
		bool
		operator<(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() < right.base());
		}

	template<class U>
		bool
		operator>(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() > right.base());
		}

	template<class U>
		bool
		operator<=(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() <= right.base());
		}

	template<class U>
		bool
		operator>=(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (left.base() >= right.base());
		}

//	template<class U>
//		typename VectorIterator<U>::difference_type
//		operator+(typename VectorIterator<U>::difference_type x, VectorIterator<U> right)
//		{
//
//		}

	template<class U>
		typename VectorIterator<U>::difference_type
		operator-(const VectorIterator<U> &left, const VectorIterator<U> &right)
		{
			return (static_cast<typename VectorIterator<U>::difference_type>(left.base() - right.base()));
		}

	template<class T, class Alloc = std::allocator<T> >
		class Vector
		{
			public:
				typedef T value_type;
				typedef Alloc allocator_type;
				typedef typename Alloc::reference reference;
				typedef typename Alloc::const_reference const_reference;
				typedef typename Alloc::pointer pointer;
				typedef typename Alloc::const_pointer const_pointer;
				typedef VectorIterator<pointer> iterator;
				typedef VectorIterator<const_pointer> const_iterator;
				//				typedef int reverse_iterator;
//				typedef int const_reverse_iterator;
				typedef ptrdiff_t difference_type;
				typedef size_t size_type;

			private:
				allocator_type _allocator;
				pointer _begin;
				pointer _end;
				pointer _end_capacity;

			private:
				void
				throw_max_size(void) const
				{
					throw std::length_error("max size reached");
				}

				void
				throw_out_of_bound(void) const
				{
					throw std::out_of_range("Vector");
				}

				void
				allocate(size_type n)
				{
					if (n > max_size())
						throw_max_size();
					_begin = _end = _allocator.allocate(n);
					_end_capacity = _begin + n;
				}

				void
				deallocate()
				{
					if (_begin)
					{
						clear();
						_allocator.deallocate(_begin, capacity());
						_begin = _end = _end_capacity = NULL;
					}
				}

				inline void
				destruct_at_end(pointer new_end)
				{
					pointer end = _end;

					while (new_end != end)
						ft::destruct(--end);
					_end = new_end;
				}

				size_type
				recommend(size_type new_size) const
				{
					const size_type max = max_size();

					if (new_size > max)
						throw_max_size();

					const size_type capacity = this->capacity();

					if (capacity >= max / 2)
						return (max);

					return ft::max<size_type>(2 * capacity, new_size);
				}

				void
				append(size_type n, const_reference val)
				{
					size_type new_size = size() + n;

					if (new_size >= capacity())
						reserve(new_size);

					_end = ft::construct_copy(_end, val, n);
				}

			public:
				explicit
				Vector(const allocator_type &alloc = allocator_type()) :
				        _allocator(alloc),
				        _begin(NULL),
				        _end(NULL),
				        _end_capacity(NULL)
				{
				}

				explicit
				Vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
				        _allocator(alloc),
				        _begin(NULL),
				        _end(NULL),
				        _end_capacity(NULL)
				{
					if (n)
						assign(n, val);
				}

				template<class InputIterator>
					Vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :
					        _allocator(alloc),
					        _begin(NULL),
					        _end(NULL),
					        _end_capacity(NULL)
					{
						assign(first, last);
					}

				Vector(const Vector &x) :
				        _allocator(x._allocator),
				        _begin(NULL),
				        _end(NULL),
				        _end_capacity(NULL)
				{
					operator =(x);
				}

				virtual
				~Vector()
				{
					deallocate();
				}

				Vector&
				operator=(const Vector<T> &other)
				{
					if (this != &other)
						assign(other.begin(), other.end());

					return (*this);
				}

				iterator
				begin()
				{
					return (iterator(&(front())));
				}

				const_iterator
				begin() const
				{
					return (const_iterator(&(front())));
				}

				iterator
				end()
				{
					return (iterator(&(back()) + 1));
				}

				const_iterator
				end() const
				{
					return (const_iterator(&(back()) + 1));
				}

				size_type
				size() const
				{
					return (static_cast<size_type>(_end - _begin));
				}

				size_type
				max_size() const
				{
					return (std::numeric_limits<size_type>::max() / sizeof(value_type));
				}

				void
				resize(size_type n, value_type val = value_type())
				{
					size_type len = size();

					if (len < n)
						append(n - len, val);
					else if (len > n)
						destruct_at_end(_begin + n);
				}

				size_type
				capacity() const
				{
					return (static_cast<size_type>(_end_capacity - _begin));
				}

				bool
				empty() const
				{
					return (_end == _begin);
				}

				void
				reserve(size_type n)
				{
					if (n < size())
						return;

					if (n > max_size())
						throw_max_size();

					pointer arr = _allocator.allocate(n);

					size_type len = size();

					if (_begin)
						ft::move(arr, _begin, len);

					if (_begin)
						_allocator.deallocate(_begin, capacity());

					_begin = arr;
					_end = _begin + len;
					_end_capacity = _begin + n;
				}

				reference
				operator[](size_type n)
				{
					return (_begin[n]);
				}

				const_reference
				operator[](size_type n) const
				{
					return (_begin[n]);
				}

				reference
				at(size_type n)
				{
					if (n >= size())
						throw_out_of_bound();

					return (_begin[n]);
				}

				const_reference
				at(size_type n) const
				{
					if (n >= size())
						throw_out_of_bound();

					return (_begin[n]);
				}

				reference
				front()
				{
					return (*_begin);
				}

				const_reference
				front() const
				{
					return (*_begin);
				}

				reference
				back()
				{
					return (*(_end - 1));
				}

				const_reference
				back() const
				{
					return (*(_end - 1));
				}

				void
				assign(size_type n, const_reference val)
				{
					clear();

					if (n > 0)
					{
						ft::Vector<T> v;
						v.reserve(n);

						v._end = ft::construct_copy(v._begin, val, n);

						swap(v);
					}
				}

				template<class InputIterator>
					void
					assign(InputIterator first, InputIterator last)
					{
						clear();

						if (first != last)
						{
							difference_type n = last - first;

							ft::Vector<T> v;
							v.reserve(n);

							pointer start = v._begin;

							while (first != last)
							{
								v._end = ft::construct_copy(start++, *first);
								first++;
							}

							swap(v);
						}
					}

				void
				push_back(const_reference val)
				{
					if (_end == _end_capacity)
						reserve(recommend(size() + 1));

					ft::construct_copy(_end++, val);
				}

				void
				pop_back()
				{
					destruct_at_end(_end - 1);
				}

				iterator
				insert(iterator position, const value_type &val)
				{
					return (position);
				}

				void
				insert(iterator position, size_type n, const value_type &val)
				{
					while (n--)
						insert(position, val);
				}

				template<class InputIterator>
					void
					insert(iterator position, InputIterator first, InputIterator last)
					{
					}

				iterator
				erase(iterator position)
				{
					return (position);
				}

				iterator
				erase(iterator first, iterator last)
				{
					return (first);
				}

				void
				swap(Vector &x)
				{
					if (this != &x)
					{
						ft::swap(_begin, x._begin);
						ft::swap(_end, x._end);
						ft::swap(_end_capacity, x._end_capacity);
					}
				}

				void
				clear()
				{
					destruct_at_end(_begin);
				}

			private:
				template<class T1, class Alloc1, class T2, class Alloc2>
					friend bool
					operator==(const Vector<T1, Alloc1> &left, const Vector<T2, Alloc2> &right);

		};

	template<class T, class Alloc>
		bool
		operator==(const Vector<T, Alloc> &left, const Vector<T, Alloc> &right)
		{
			typedef typename Vector<T, Alloc>::size_type size_type;

			size_type len = left.size();

			if (len != right.size())
				return (false);

			for (size_type index = 0; index < len; index++)
				if (!(left[index] == right[index]))
					return (false);

			return (true);
		}

	template<class T, class Alloc>
		void
		swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y)
		{
			x.swap(y);
		}
}

#endif /* VECTOR_HPP_ */
