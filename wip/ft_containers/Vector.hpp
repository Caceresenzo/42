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
#include <TypeTraits.hpp>
#include <cstddef>
#include <limits>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace ft
{
	/**
	 * Vectors are sequence containers representing arrays that can change in size.
	 * Just like arrays, vectors use contiguous storage locations for their elements, which means that their elements can also be accessed using offsets on regular pointers to its elements, and just as efficiently as in arrays. But unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
	 * Internally, vectors use a dynamically allocated array to store their elements. This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it. This is a relatively expensive task in terms of processing time, and thus, vectors do not reallocate each time an element is added to the container.
	 * Instead, vector containers may allocate some extra storage to accommodate for possible growth, and thus the container may have an actual capacity greater than the storage strictly needed to contain its elements (i.e., its size). Libraries can implement different strategies for growth to balance between memory usage and reallocations, but in any case, reallocations should only happen at logarithmically growing intervals of size so that the insertion of individual elements at the end of the vector can be provided with amortized constant time complexity (see push_back).
	 * Therefore, compared to arrays, vectors consume more memory in exchange for the ability to manage storage and grow dynamically in an efficient way.
	 * Compared to the other dynamic sequence containers (deques, lists and forward_lists), vectors are very efficient accessing its elements (just like arrays) and relatively efficient adding or removing elements from its end. For operations that involve inserting or removing elements at positions other than the end, they perform worse than the others, and have less consistent iterators and references than lists and forward_lists.
	 *
	 * @tparam T Type of the elements.
	 * @tparam Alloc Type of the allocator object used to define the storage allocation model.
	 */
	template<class T, class Alloc = std::allocator<T> >
		class Vector
		{
			public:

			public:
				/** The first template parameter (T) */
				typedef T value_type;

				/** The second template parameter (Alloc) */
				typedef Alloc allocator_type;

				/** allocator_type::reference */
				typedef typename Alloc::reference reference;

				/** allocator_type::const_reference */
				typedef typename Alloc::const_reference const_reference;

				/** allocator_type::pointer */
				typedef typename Alloc::pointer pointer;

				/** allocator_type::const_pointer */
				typedef typename Alloc::const_pointer const_pointer;

				/** A random access iterator to value_type */
				typedef ft::normal_iterator<pointer> iterator;

				/** A random access iterator to const value_type */
				typedef ft::normal_iterator<const_pointer> const_iterator;

				/** A reverse random access iterator to value_type */
				typedef ft::reverse_iterator<iterator> reverse_iterator;

				/** A reverse random access iterator to const value_type */
				typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

				/** A signed integral type */
				typedef ptrdiff_t difference_type;

				/** An unsigned integral type that can represent any non-negative value of difference_type */
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

			public:
				/**
				 * Constructs an empty container, with no elements.
				 *
				 * @param alloc Allocator object.
				 */
				explicit
				Vector(const allocator_type &alloc = allocator_type()) :
						_allocator(alloc),
						_begin(NULL),
						_end(NULL),
						_end_capacity(NULL)
				{
				}

				/**
				 * Constructs a container with n elements. Each element is a copy of val.
				 *
				 * @param n Initial container size (i.e., the number of elements in the container at construction).
				 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
				 * @param alloc Allocator object.
				 */
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

				/**
				 * Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
				 *
				 * @tparam InputIterator Input iterator type.
				 * @param first Input iterator to the initial position in a range.
				 * @param last Input iterator to the final position in a range.
				 * @param alloc Allocator object.
				 * @param isIterator C++ template that disable this constructor in cast of the type being an integral.
				 */
				template<class InputIterator>
					Vector(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type &alloc = allocator_type()) :
							_allocator(alloc),
							_begin(NULL),
							_end(NULL),
							_end_capacity(NULL)
					{
						assign(first, last);
					}

				/**
				 * Constructs a container with a copy of each of the elements in x, in the same order.
				 *
				 * @param x Another vector object of the same type (with the same class template arguments T and Alloc), whose contents are either copied or acquired.
				 */
				Vector(const Vector &x) :
						_allocator(x._allocator),
						_begin(NULL),
						_end(NULL),
						_end_capacity(NULL)
				{
					operator =(x);
				}

				/**
				 * This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
				 */
				virtual
				~Vector()
				{
					deallocate();
				}

				/**
				 * Copies all the elements from x into the container.
				 * The container preserves its current allocator, which is used to allocate storage in case of reallocation.
				 *
				 * @param x A vector object of the same type (i.e., with the same template parameters, T and Alloc).
				 * @return *this
				 */
				Vector&
				operator=(const Vector<T> &x)
				{
					if (this != &x)
						assign(x.begin(), x.end());

					return (*this);
				}

				/**
				 * Returns an iterator pointing to the first element in the vector.
				 * Notice that, unlike member ::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
				 * If the container is empty, the returned iterator value shall not be dereferenced.
				 *
				 * @return An iterator to the beginning of the sequence container.
				 */
				iterator
				begin()
				{
					return (iterator(&(front())));
				}

				/**
				 * Returns an iterator pointing to the first element in the vector.
				 * Notice that, unlike member ::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
				 * If the container is empty, the returned iterator value shall not be dereferenced.
				 *
				 * @return A const-qualified iterator to the beginning of the sequence container.
				 */
				const_iterator
				begin() const
				{
					return (const_iterator(&(front())));
				}

				/**
				 * Returns an iterator referring to the past-the-end element in the vector container.
				 * The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
				 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with vector::begin to specify a range including all the elements in the container.
				 * If the container is empty, this function returns the same as vector::begin.
				 *
				 * @return An iterator to the element past the end of the sequence.
				 */
				iterator
				end()
				{
					return (iterator(&(back()) + 1));
				}

				/**
				 * Returns an iterator referring to the past-the-end element in the vector container.
				 * The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
				 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with vector::begin to specify a range including all the elements in the container.
				 * If the container is empty, this function returns the same as vector::begin.
				 *
				 * @return An const-qualified iterator to the element past the end of the sequence.
				 */
				const_iterator
				end() const
				{
					return (const_iterator(&(back()) + 1));
				}

				/**
				 * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
				 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				 * ::rbegin points to the element right before the one that would be pointed to by member ::end.
				 *
				 * @return A reverse iterator to the reverse beginning of the sequence container.
				 */
				reverse_iterator
				rbegin()
				{
					return (reverse_iterator(end()));
				}

				/**
				 * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
				 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				 * ::rbegin points to the element right before the one that would be pointed to by member ::end.
				 *
				 * @return A const-qualified reverse iterator to the reverse beginning of the sequence container.
				 */
				const_reverse_iterator
				rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				/**
				 * Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
				 * The range between ::rbegin and ::rend contains all the elements of the vector (in reverse order).
				 *
				 * @return A reverse iterator to the reverse end of the sequence container.
				 */
				reverse_iterator
				rend()
				{
					return (reverse_iterator(begin()));
				}

				/**
				 * Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
				 * The range between ::rbegin and ::rend contains all the elements of the vector (in reverse order).
				 *
				 * @return A const-qualified reverse iterator to the reverse end of the sequence container.
				 */
				const_reverse_iterator
				rend() const
				{
					return (const_reverse_iterator(begin()));
				}

				/**
				 * Returns the number of elements in the vector.
				 * This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
				 *
				 * @return The number of elements in the container.
				 */
				size_type
				size() const
				{
					return (static_cast<size_type>(_end - _begin));
				}

				/**
				 * Returns the maximum number of elements that the vector can hold.
				 * This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
				 *
				 * @return The maximum number of elements a vector container can hold as content.
				 */
				size_type
				max_size() const
				{
					return (_allocator.max_size());
				}

				/**
				 * Resizes the container so that it contains n elements.
				 * If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
				 * If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
				 * If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
				 * Notice that this function changes the actual content of the container by inserting or erasing elements from it.
				 *
				 * @param n New container size, expressed in number of elements.
				 * @param val Object whose content is copied to the added elements in case that n is greater than the current container size. If not specified, the default constructor is used instead.
				 */
				void
				resize(size_type n, value_type val = value_type())
				{
					size_type len = size();

					if (n < len)
						erase(begin() + n, end());
					else if (n > size())
						insert(end(), n - len, val);
				}

				/**
				 * Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
				 * This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
				 * Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
				 * The capacity of a vector can be explicitly altered by calling member ::reserve.
				 *
				 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
				 */
				size_type
				capacity() const
				{
					return (static_cast<size_type>(_end_capacity - _begin));
				}

				/**
				 * Returns whether the vector is empty (i.e. whether its size is 0).
				 * This function does not modify the container in any way. To clear the content of a vector, see ::clear.
				 *
				 * @return true if the container size is 0, false otherwise.
				 */
				bool
				empty() const
				{
					return (_end == _begin);
				}

				/**
				 * Requests that the vector capacity be at least enough to contain n elements.
				 * If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
				 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
				 * This function has no effect on the vector size and cannot alter its elements.
				 *
				 * @param n Minimum capacity for the vector. Note that the resulting vector capacity may be equal or greater than n.
				 */
				void
				reserve(size_type n)
				{
					if (n < capacity())
						return;

					if (n > max_size())
						throw_max_size();

					size_type len = size();

					pointer arr = _allocator.allocate(n);

					if (_begin)
					{
						ft::copy(_begin, _end, arr);

						_allocator.deallocate(_begin, capacity());
					}

					_begin = arr;
					_end = _begin + len;
					_end_capacity = _begin + n;
				}

				/**
				 * Returns a reference to the element at position n in the vector container.
				 * A similar member function, ::at, has the same behavior as this operator function, except that ::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
				 * Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
				 *
				 * @param n Position of an element in the container. Notice that the first element has a position of 0 (not 1).
				 * @return The element at the specified position in the vector.
				 */
				reference
				operator[](size_type n)
				{
					return (_begin[n]);
				}

				/**
				 * Returns a reference to the element at position n in the vector container.
				 * A similar member function, ::at, has the same behavior as this operator function, except that ::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
				 * Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
				 *
				 * @param n Position of an element in the container. Notice that the first element has a position of 0 (not 1).
				 * @return The element at the specified position in the vector.
				 */
				const_reference
				operator[](size_type n) const
				{
					return (_begin[n]);
				}

				/**
				 * Returns a reference to the element at position n in the vector.
				 * The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member ::operator[], that does not check against bounds.
				 *
				 * @param n Position of an element in the container.
				 * @return The element at the specified position in the container.
				 * @throws out_of_range If n is greater than, or equal to, the vector size.
				 */
				reference
				at(size_type n)
				{
					if (n >= size())
						throw_out_of_bound();

					return (_begin[n]);
				}

				/**
				 * Returns a reference to the element at position n in the vector.
				 * The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member ::operator[], that does not check against bounds.
				 *
				 * @param n Position of an element in the container.
				 * @return The element at the specified position in the container.
				 * @throws out_of_range If n is greater than, or equal to, the vector size.
				 */
				const_reference
				at(size_type n) const
				{
					if (n >= size())
						throw_out_of_bound();

					return (_begin[n]);
				}

				/**
				 * Returns a reference to the first element in the vector.
				 * Unlike member ::begin, which returns an iterator to this same element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the first element in the vector container.
				 */
				reference
				front()
				{
					return (*_begin);
				}

				/**
				 * Returns a reference to the first element in the vector.
				 * Unlike member ::begin, which returns an iterator to this same element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the first element in the vector container.
				 */
				const_reference
				front() const
				{
					return (*_begin);
				}

				/**
				 * Returns a reference to the last element in the vector.
				 * Unlike member ::end, which returns an iterator just past this element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the last element in the vector.
				 */
				reference
				back()
				{
					return (*(_end - 1));
				}

				/**
				 * Returns a reference to the last element in the vector.
				 * Unlike member ::end, which returns an iterator just past this element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the last element in the vector.
				 */
				const_reference
				back() const
				{
					return (*(_end - 1));
				}

				/**
				 * Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
				 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 *
				 * @tparam InputIterator Input iterator type that points to elements of a type from which value_type objects can be constructed.
				 * @param first Input iterators to the initial position in a sequence. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last
				 * @param last Input iterators to the final position in a sequence. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
				 */
				template<class InputIterator>
					void
					assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type isIterator = InputIterator())
					{
						(void)isIterator;

						clear();
						insert(begin(), first, last);
					}

				/**
				 * Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
				 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 *
				 * @param n New size for the container.
				 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
				 */
				void
				assign(size_type n, const_reference val)
				{
					clear();
					insert(begin(), n, val);
				}

				/**
				 * Adds a new element at the end of the vector, after its current last element. The content of val is copied to the new element.
				 * This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 *
				 * @param val Value to be copied to the new element.
				 */
				void
				push_back(const_reference val)
				{
					if (_end == _end_capacity)
					{
						value_type copy = value_type(val);

						reserve(recommend(size() + 1));

						ft::construct_copy(_end++, copy);
					}
					else
						ft::construct_copy(_end++, val);
				}

				/**
				 * Removes the last element in the vector, effectively reducing the container size by one.
				 */
				void
				pop_back()
				{
					erase(end() - 1);
				}

				/**
				 * The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 * Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
				 * The parameters determine how many elements are inserted and to which values they are initialized:
				 *
				 * @param position Position in the vector where the new elements are inserted.
				 * @param val Value to be copied to the inserted elements.
				 * @return An iterator that points to the first of the newly inserted elements.
				 */
				iterator
				insert(iterator position, const value_type &val)
				{
					difference_type offset = position - begin();

					insert(position, 1, val);

					return (iterator(begin() + offset));
				}

				/**
				 * The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 * Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
				 * The parameters determine how many elements are inserted and to which values they are initialized:
				 *
				 * @param position Position in the vector where the new elements are inserted.
				 * @param n Number of elements to insert. Each element is initialized to a copy of val.
				 * @param val Value to be copied to the inserted elements.
				 */
				void
				insert(iterator position, size_type n, const value_type &val)
				{
					if (n)
					{
						Vector v;
						v.reserve(size() + n);

						iterator it = begin();
						while (it != position)
							v.push_back(*(it++));
						while (n--)
							v.push_back(val);
						while (it != end())
							v.push_back(*(it++));

						swap(v);
					}
				}

				/**
				 * The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				 *
				 * @tparam InputIterator Input iterator type that points to elements of a type from which value_type objects can be constructed.
				 * @param position Position in the vector where the new elements are inserted.
				 * @param first Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
				 * @param last Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
				 */
				template<class InputIterator>
					void
					insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type isIterator = InputIterator())
					{
						(void)isIterator;

						if (first != last)
						{
							Vector v;
							v.reserve(size() + ft::abs(last - first));

							iterator it = begin();
							while (it != position)
								v.push_back(*(it++));
							while (first != last)
								v.push_back(*(first++));
							while (it != end())
								v.push_back(*(it++));

							swap(v);
						}
					}

				/**
				 * Removes from the vector a single element.
				 * This effectively reduces the container size by the number of elements removed, which are destroyed.
				 *
				 * @param position Iterator pointing to a single element to be removed from the vector.
				 * @return An iterator pointing to the new location of the element that followed the last element erased by the function call. This is the container end if the operation erased the last element in the sequence.
				 */
				iterator
				erase(iterator position)
				{
					return (erase(position, position + 1));
				}

				/**
				 * Removes from the vector a range of elements.
				 * This effectively reduces the container size by the number of elements removed, which are destroyed.
				 *
				 * @param position Iterator pointing to a single element to be removed from the vector.
				 * @return An iterator pointing to the new location of the element that followed the last element erased by the function call. This is the container end if the operation erased the last element in the sequence.
				 */
				iterator
				erase(iterator first, iterator last)
				{
					if (first != last)
					{
						difference_type n = last - first;

						ft::copy(last, end(), first);
						ft::destruct(_end - n, n);

						_end -= n;
					}

					return (iterator(first));
				}

				/**
				 * Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
				 * After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
				 *
				 * @param x Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc) whose content is swapped with that of this container.
				 */
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

				/**
				 * Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
				 */
				void
				clear()
				{
					erase(begin(), end());
				}
		}
		;

	template<class T, class Alloc>
		bool
		operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template<class T, class Alloc>
		bool
		operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

	template<class T, class Alloc>
		bool
		operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template<class T, class Alloc>
		bool
		operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (!(rhs < lhs));
		}

	template<class T, class Alloc>
		bool
		operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (rhs < lhs);
		}

	template<class T, class Alloc>
		bool
		operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
		{
			return (!(lhs < rhs));
		}

	template<class T, class Alloc>
		void
		swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y)
		{
			x.swap(y);
		}
}

#endif /* VECTOR_HPP_ */
