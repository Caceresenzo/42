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

#include <bits/allocator.h>
#include <Function.hpp>
#include <Functional.hpp>
#include <Iterator.hpp>
#include <RedBlackTree.hpp>
#include <Utility.hpp>
#include <iostream>

namespace ft
{

	template<class Key, class T/*, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key, T> > */>
		class Map
		{
				typedef less<Key> Compare;
				typedef std::allocator<pair<const Key, T> > Alloc;

			private:
				typedef RedBlackTree<Key, T/*, Compare, Alloc*/> red_black_tree_type;

			public:
				/** The first template parameter (Key). **/
				typedef typename red_black_tree_type::key_type key_type;

				/** The second template parameter (T). */
				typedef typename red_black_tree_type::mapped_type mapped_type;

				/** pair<const key_type, mapped_type> */
				typedef typename red_black_tree_type::value_type value_type;

				/** The third template parameter (Compare). */
				typedef typename red_black_tree_type::key_compare key_compare;

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
				typedef typename red_black_tree_type::allocator_type allocator_type;

				/** allocator_type::reference */
				typedef typename red_black_tree_type::reference reference;

				/** allocator_type::reference */
				typedef typename red_black_tree_type::const_reference const_reference;

				/** allocator_type::pointer */
				typedef typename red_black_tree_type::pointer pointer;

				/** allocator_type::const_pointer */
				typedef typename red_black_tree_type::const_pointer const_pointer;

				/** a bidirectional iterator to value_type */
				typedef typename red_black_tree_type::iterator iterator;

				/** a bidirectional iterator to const value_type */
				typedef typename red_black_tree_type::const_iterator const_iterator;

				/** reverse_iterator<iterator> */
				typedef ft::reverse_iterator<iterator> reverse_iterator;

				/** reverse_iterator<const_iterator> */
				typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

				/** a signed integral type, identical to: iterator_traits<iterator>::difference_type */
				typedef typename red_black_tree_type::difference_type difference_type;

				/** an unsigned integral type that can represent any non-negative value of difference_type. */
				typedef typename red_black_tree_type::size_type size_type;

			private:
				red_black_tree_type m_tree;

			public:
				explicit
				Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
						m_tree(comp, alloc)
				{
				}

				template<class InputIterator>
					Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
							m_tree(comp, alloc)
					{
						insert_iter_impl(first, last);
					}

				Map(const Map &x) :
						m_tree(x.m_tree.m_compare, x.m_tree.m_allocator)
				{
					insert_iter_impl(x.begin(), x.end());
				}

				~Map()
				{
					clear();
				}

				Map&
				operator=(const Map &x)
				{
					if (this != &x)
						m_tree = x.m_tree;

					return (*this);
				}

				iterator
				begin()
				{
					return (m_tree.begin());
				}

				const_iterator
				begin() const
				{
					return (m_tree.begin());
				}

				iterator
				end()
				{
					return (m_tree.end());
				}

				const_iterator
				end() const
				{
					return (m_tree.end());
				}

				reverse_iterator
				rbegin()
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator
				rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator
				rend()
				{
					return (reverse_iterator(begin()));
				}

				const_reverse_iterator
				rend() const
				{
					return (const_reverse_iterator(begin()));
				}

				bool
				empty() const
				{
					return (m_tree.empty());
				}

				size_type
				size() const
				{
					return (m_tree.size());
				}

				size_type
				max_size() const
				{
					return (m_tree.max_size());
				}

				mapped_type&
				operator[](const key_type &k)
				{
					return ((*((insert(make_pair(k, mapped_type()))).first)).second);
				}

				pair<iterator, bool>
				insert(const value_type &val)
				{
					return (m_tree.insert(val));
				}

				iterator
				insert(iterator position, const value_type &val)
				{
					(void)position;

					return (m_tree.insert(val));
				}

				template<class InputIterator>
					void
					insert(InputIterator first, InputIterator last)
					{
						Map map(first, last);

						insert_iter_impl(map.begin(), map.end());
					}

				void
				erase(iterator position)
				{
					m_tree.erase(position.node());
				}

				size_type
				erase(const key_type &k)
				{
					return (m_tree.erase(k));
				}

				void
				erase(iterator first, iterator last)
				{
					return (m_tree.erase(first.node(), last.node()));
				}

				void
				swap(Map &x)
				{
					m_tree.swap(x.m_tree);
				}

				void
				clear()
				{
					m_tree.clear();
				}

				key_compare
				key_comp() const
				{
					return (m_tree.key_comp());
				}

				value_compare
				value_comp() const
				{
					return (value_compare());
				}

				iterator
				find(const key_type &k)
				{
					return (m_tree.find(k));
				}

				const_iterator
				find(const key_type &k) const
				{
					return (m_tree.find(k));
				}

				size_type
				count(const key_type &k) const
				{
					return (find(k) != end() ? 1 : 0);
				}

				iterator
				lower_bound(const key_type &k)
				{
					return (m_tree.lower_bound(k));
				}

				const_iterator
				lower_bound(const key_type &k) const
				{
					return (m_tree.lower_bound(k));
				}

				iterator
				upper_bound(const key_type &k)
				{
					return (m_tree.upper_bound(k));
				}

				const_iterator
				upper_bound(const key_type &k) const
				{
					return (m_tree.upper_bound(k));
				}

				pair<iterator, iterator>
				equal_range(const key_type &k)
				{
					typedef typename red_black_tree_type::node_base_type node;
					pair<node, node> pr = m_tree.equal_range(k);

					return (make_pair(pr.first, pr.second));
				}

				pair<const_iterator, const_iterator>
				equal_range(const key_type &k) const
				{
					typedef typename red_black_tree_type::node_base_const_type node;
					pair<node, node> pr = m_tree.equal_range(k);

					return (make_pair(pr.first, pr.second));
				}

			private:
				template<class InputIterator>
					void
					insert_iter_impl(InputIterator first, InputIterator last)
					{
						while (first != last)
							insert(*first++);
					}

			public:
				void
				dump()
				{
					m_tree.dump();
				}
		};
}

#endif /* MAP_HPP_ */
