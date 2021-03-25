/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:38:07 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/20 01:38:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
# define MAP_HPP_

#include <memory>

# include "BinarySearchTree.hpp"
# include "Function.hpp"
# include "Functional.hpp"
# include "Iterator.hpp"
# include "Utility.hpp"

namespace ft
{
	template<class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
		class Map
		{
			private:
				typedef BinarySearchTree<Key, T, Compare, Alloc> tree_type;

			public:
				/** The first template parameter (Key). **/
				typedef typename tree_type::key_type key_type;

				/** The second template parameter (T). */
				typedef typename tree_type::mapped_type mapped_type;

				/** pair<const key_type, mapped_type> */
				typedef typename tree_type::value_type value_type;

				/** The third template parameter (Compare). */
				typedef typename tree_type::key_compare key_compare;

				/** Nested function class to compare elements. */
				class value_compare :
						public ft::binary_function<value_type, value_type, bool>
				{
					private:
						key_compare m_comparator;

					protected:
						value_compare(key_compare comparator) :
								m_comparator(comparator)
						{
						}

					public:
						bool
						operator()(const value_type &x, const value_type &y) const
						{
							return (m_comparator(x.first, y.first));
						}
				};

				/** The fourth template parameter (Alloc). */
				typedef typename tree_type::allocator_type allocator_type;

				/** allocator_type::reference */
				typedef typename tree_type::reference reference;

				/** allocator_type::reference */
				typedef typename tree_type::const_reference const_reference;

				/** allocator_type::pointer */
				typedef typename tree_type::pointer pointer;

				/** allocator_type::const_pointer */
				typedef typename tree_type::const_pointer const_pointer;

				/** a bidirectional iterator to value_type */
				typedef typename tree_type::iterator iterator;

				/** a bidirectional iterator to const value_type */
				typedef typename tree_type::const_iterator const_iterator;

				/** reverse_iterator<iterator> */
				typedef ft::reverse_iterator<iterator> reverse_iterator;

				/** reverse_iterator<const_iterator> */
				typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

				/** a signed integral type, identical to: iterator_traits<iterator>::difference_type */
				typedef typename tree_type::difference_type difference_type;

				/** an unsigned integral type that can represent any non-negative value of difference_type. */
				typedef typename tree_type::size_type size_type;

			private:
				allocator_type m_allocator;
				tree_type m_tree;

			public:
				/**
				 * Constructs an empty container.
				 *
				 * @param comp Comparison function object to use for all comparisons of keys.
				 * @param alloc Allocator to use for all memory allocations of this container.
				 */
				explicit
				Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
						m_allocator(alloc),
						m_tree(comp, alloc)
				{
				}

				/**
				 * Constructs the container with the contents of the range [first, last).
				 * If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
				 *
				 * @tparam InputIterator Input iterator type.
				 * @param first Input iterator to the initial position in a range.
				 * @param last Input iterator to the final position in a range.
				 * @param comp Comparison function object to use for all comparisons of keys.
				 * @param alloc Allocator to use for all memory allocations of this container.
				 */
				template<class InputIterator>
					Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
							m_allocator(alloc),
							m_tree(comp, alloc)
					{
						insert_iter_impl(first, last);
					}

				/**
				 * Copy constructor.
				 * Constructs the container with the copy of the contents of other.
				 *
				 * @param x Another container to be used as source to initialize the elements of the container with.
				 */
				Map(const Map &x) :
						m_allocator(x.m_allocator),
						m_tree(x.m_tree.key_comparator(), x.m_allocator)
				{
					insert_iter_impl(x.begin(), x.end());
				}

				/**
				 * Destructs the map.
				 * The destructors of the elements are called and the used storage is deallocated.
				 * Note, that if the elements are pointers, the pointed-to objects are not destroyed.
				 */
				~Map()
				{
					clear();
				}

				/**
				 * Copy assignment operator. Replaces the contents with a copy of the contents of other.
				 *
				 * @param x Another container to use as data source.
				 */
				Map&
				operator=(const Map &x)
				{
					if (this != &x)
						m_tree = x.m_tree;

					return (*this);
				}

				/**
				 * Returns an iterator to the first element of the map.
				 * If the map is empty, the returned iterator will be equal to end().
				 *
				 * @return An iterator to the first element.
				 */
				iterator
				begin()
				{
					return (m_tree.begin());
				}

				/**
				 * Returns an iterator to the first element of the map.
				 * If the map is empty, the returned iterator will be equal to end().
				 *
				 * @return A const-qualified iterator to the first element.
				 */
				const_iterator
				begin() const
				{
					return (m_tree.begin());
				}

				/**
				 * Returns an iterator to the element following the last element of the map.
				 * This element acts as a placeholder; attempting to access it results in undefined behavior.
				 *
				 * @return An iterator to the element following the last element.
				 */
				iterator
				end()
				{
					return (m_tree.end());
				}

				/**
				 * Returns an iterator to the element following the last element of the map.
				 * This element acts as a placeholder; attempting to access it results in undefined behavior.
				 *
				 * @return A const-qualified iterator to the element following the last element.
				 */
				const_iterator
				end() const
				{
					return (m_tree.end());
				}

				/**
				 * Returns a reverse iterator to the first element of the reversed map.
				 * It corresponds to the last element of the non-reversed map.
				 * If the map is empty, the returned iterator is equal to rend().
				 *
				 * @return A reverse iterator to the first element.
				 */
				reverse_iterator
				rbegin()
				{
					return (reverse_iterator(end()));
				}

				/**
				 * Returns a reverse iterator to the first element of the reversed map.
				 * It corresponds to the last element of the non-reversed map.
				 * If the map is empty, the returned iterator is equal to rend().
				 *
				 * @return A const-qualified reverse iterator to the first element.
				 */
				const_reverse_iterator
				rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				/**
				 * Returns a reverse iterator to the element following the last element of the reversed map.
				 * It corresponds to the element preceding the first element of the non-reversed map.
				 * This element acts as a placeholder, attempting to access it results in undefined behavior.
				 *
				 * @return A reverse iterator to the element following the last element.
				 */
				reverse_iterator
				rend()
				{
					return (reverse_iterator(begin()));
				}

				/**
				 * Returns a reverse iterator to the element following the last element of the reversed map.
				 * It corresponds to the element preceding the first element of the non-reversed map.
				 * This element acts as a placeholder, attempting to access it results in undefined behavior.
				 *
				 * @return A const-qualified reverse iterator to the element following the last element.
				 */
				const_reverse_iterator
				rend() const
				{
					return (const_reverse_iterator(begin()));
				}

				/**
				 * Checks if the container has no elements, i.e. whether begin() == end().
				 *
				 * @return true if the container is empty, false otherwise.
				 */
				bool
				empty() const
				{
					return (m_tree.empty());
				}

				/**
				 * Returns the number of elements in the container, i.e. std::distance(begin(), end()).
				 *
				 * @return The number of elements in the container.
				 */
				size_type
				size() const
				{
					return (m_tree.size());
				}

				/**
				 * Returns the maximum number of elements the container is able to hold due to system or library implementation limitations, i.e. std::distance(begin(), end()) for the largest container.
				 *
				 * @return Maximum number of elements.
				 */
				size_type
				max_size() const
				{
					return (m_tree.max_size());
				}

				/**
				 * Returns a reference to the value that is mapped to a key equivalent to key, performing an insertion if such key does not already exist.
				 *
				 * @param The key of the element to find.
				 * @return Reference to the mapped value of the new element if no element with key key existed. Otherwise a reference to the mapped value of the existing element whose key is equivalent to key.
				 */
				mapped_type&
				operator[](const key_type &k)
				{
					return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
				}

				/**
				 * Inserts value.
				 *
				 * @param val Element value to insert.
				 * @return Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a bool denoting whether the insertion took place.
				 */
				pair<iterator, bool>
				insert(const value_type &val)
				{
					pair<typename tree_type::node_type*, bool> pr = m_tree.insert(val);

					return (ft::make_pair(iterator(pr.first), pr.second));
				}

				/**
				 * Inserts value in the position as close as possible.
				 *
				 * @param position Hint used as a suggestion as to where to start the search.
				 * @param val Element value to insert.
				 * @return An iterator to the inserted element, or to the element that prevented the insertion.
				 * @implSpec The hint position is discarded.
				 */
				iterator
				insert(iterator position, const value_type &val)
				{
					(void)position;

					return (insert(val).first);
				}

				/**
				 * Inserts elements from range [first, last).
				 *
				 * @tparam InputIterator Input iterator type.
				 * @param first Input iterator to the initial position in a range.
				 * @param last Input iterator to the final position in a range.
				 */
				template<class InputIterator>
					void
					insert(InputIterator first, InputIterator last)
					{
						Map map(first, last);

						insert_iter_impl(map.begin(), map.end());
					}

				/**
				 * Removes the element at position.
				 *
				 * @param position Iterator to the element to remove.
				 */
				void
				erase(iterator position)
				{
					m_tree.erase(position.node());
				}

				/**
				 * Removes the element (if one exists) with the key equivalent to key.
				 *
				 * @param k Key value of the elements to remove.
				 * @return Number of elements removed (0 or 1).
				 */
				size_type
				erase(const key_type &k)
				{
					return (m_tree.erase(k));
				}
				/**
				 * Removes the elements in the range [first; last), which must be a valid range in *this.
				 *
				 * @param first Input iterator to the initial position in a range.
				 * @param last Input iterator to the final position in a range.
				 */
				void
				erase(iterator first, iterator last)
				{
					m_tree.erase(first.node(), last.node());
				}

				/**
				 * Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
				 *
				 * @param x Container to exchange the contents with.
				 */
				void
				swap(Map &x)
				{
					m_tree.swap(x.m_tree);
				}

				/**
				 * Erases all elements from the container. After this call, size() returns zero.
				 */
				void
				clear()
				{
					m_tree.clear();
				}

				/**
				 * Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
				 *
				 * @return The key comparison function object.
				 */
				key_compare
				key_comp() const
				{
					return (m_tree.key_comparator());
				}

				/**
				 * Returns a function object that compares objects of type ft::Map::value_type (key-value pairs) by using key_comp to compare the first components of the pairs.
				 *
				 * @return The value comparison function object.
				 */
				value_compare
				value_comp() const
				{
					return (value_compare());
				}

				/**
				 * Finds an element with key equivalent to key.
				 *
				 * @param k Key value of the element to search for.
				 * @return An iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
				 */
				iterator
				find(const key_type &k)
				{
					return (m_tree.find(k));
				}

				/**
				 * Finds an element with key equivalent to key.
				 *
				 * @param k Key value of the element to search for.
				 * @return A const-qualified iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
				 */
				const_iterator
				find(const key_type &k) const
				{
					return (m_tree.find(k));
				}

				/**
				 * Returns the number of elements with key that compares equivalent to the specified argument, which is either 1 or 0 since this container does not allow duplicates.
				 *
				 * @param k Key value of the elements to count.
				 * @return Number of elements with key that compares equivalent to key or x, which is either 1 or 0.
				 */
				size_type
				count(const key_type &k) const
				{
					return (find(k) != end() ? 1 : 0);
				}

				/**
				 * Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
				 *
				 * @param k Key value to compare the elements to.
				 * @return An iterator pointing to the first element that is not less than key. If no such element is found, a past-the-end iterator (see end()) is returned.
				 */
				iterator
				lower_bound(const key_type &k)
				{
					return (m_tree.lower_bound(k));
				}

				/**
				 * Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
				 *
				 * @param k Key value to compare the elements to.
				 * @return A const-qualified iterator pointing to the first element that is not less than key. If no such element is found, a past-the-end iterator (see end()) is returned.
				 */
				const_iterator
				lower_bound(const key_type &k) const
				{
					return (m_tree.lower_bound(k));
				}

				/**
				 * Returns an iterator pointing to the first element that is greater than key.
				 *
				 * @param k Key value to compare the elements to.
				 * @return An iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
				 */
				iterator
				upper_bound(const key_type &k)
				{
					return (m_tree.upper_bound(k));
				}

				/**
				 * Returns an iterator pointing to the first element that is greater than key.
				 *
				 * @param k Key value to compare the elements to.
				 * @return A const-qualified iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
				 */
				const_iterator
				upper_bound(const key_type &k) const
				{
					return (m_tree.upper_bound(k));
				}

				/**
				 * Returns a range containing all elements with the given key in the container.
				 * The range is defined by two iterators, one pointing to the first element that is not less than key and another pointing to the first element greater than key.
				 * Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
				 *
				 * @param k Key value to compare the elements to.
				 * @return ft::pair containing a pair of iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key. If there are no elements not less than key, past-the-end (see end()) iterator is returned as the first element. Similarly if there are no elements greater than key, past-the-end iterator is returned as the second element.
				 */
				pair<iterator, iterator>
				equal_range(const key_type &k)
				{
					return (ft::make_pair(m_tree.lower_bound(k), m_tree.upper_bound(k)));
				}

				/**
				 * Returns a range containing all elements with the given key in the container.
				 * The range is defined by two iterators, one pointing to the first element that is not less than key and another pointing to the first element greater than key.
				 * Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
				 *
				 * @param k Key value to compare the elements to.
				 * @return ft::pair containing a pair of const-qualified iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key. If there are no elements not less than key, past-the-end (see end()) iterator is returned as the first element. Similarly if there are no elements greater than key, past-the-end iterator is returned as the second element.
				 */
				pair<const_iterator, const_iterator>
				equal_range(const key_type &k) const
				{
					return (ft::make_pair(m_tree.lower_bound(k), m_tree.upper_bound(k)));
				}

			private:
				template<class InputIterator>
					void
					insert_iter_impl(InputIterator first, InputIterator last)
					{
						while (first != last)
							insert(*first++);
					}

#ifdef FT_MAP_DEBUG
			public:
				void
				dump()
				{
					m_tree.dump();
				}
#endif

		};

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator==(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator!=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator<(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator<=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (!(rhs < lhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator>(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (rhs < lhs);
		}

	template<class Key, class T, class Compare, class Alloc>
		bool
		operator>=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
		{
			return (!(lhs < rhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		void
		swap(Map<Key, T, Compare, Alloc> &x, Map<Key, T, Compare, Alloc> &y)
		{
			x.swap(y);
		}
}

#endif /* MAP_HPP_ */
