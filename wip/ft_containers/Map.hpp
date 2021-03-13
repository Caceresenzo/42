/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:39:25 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/11 11:39:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
# define MAP_HPP_

#include <bits/allocator.h>
#include <Function.hpp>
#include <Functional.hpp>
#include <Iterator.hpp>
#include <stddef.h>
#include <Utility.hpp>
#include <cassert>

namespace ft
{
	class BaseMapNode
	{
		public:
			typedef BaseMapNode node_type;
			typedef size_t size_type;

		private:
			int m_black_level;
			node_type *m_right;
			node_type *m_left;
			node_type *m_parent;

		public:
			BaseMapNode() :
					m_black_level(0),
					m_right(NULL),
					m_left(NULL),
					m_parent(NULL)
			{
			}

			node_type*&
			right()
			{
				return (m_right);
			}

			node_type*
			right() const
			{
				return (m_right);
			}

			node_type*&
			left()
			{
				return (m_left);
			}

			node_type*
			left() const
			{
				return (m_left);
			}

			node_type*&
			parent()
			{
				return (m_parent);
			}

			node_type*
			parent() const
			{
				return (m_parent);
			}

			bool
			is_left_child()
			{
				if (m_parent)
					return (m_parent->m_left == this);

				return (true);
			}

			bool
			is_right_child()
			{
				if (m_parent)
					return (m_parent->m_right == this);

				return (true);
			}

			int&
			black_level()
			{
				return (m_black_level);
			}
	};

	template<class Key, class T, class Compare>
		class MapNode :
				public BaseMapNode
		{
			public:
				typedef Key key_type;
				typedef T mapped_type;
				typedef pair<key_type, mapped_type> value_type;
				typedef MapNode<Key, T, Compare> node_type;
				typedef BaseMapNode::size_type size_type;

			private:
				typedef BaseMapNode base_type;
				value_type m_value;

			public:
				MapNode(const value_type &value) :
						BaseMapNode(),
						m_value(value)
				{
				}

				value_type&
				value()
				{
					return (m_value);
				}

				value_type&
				value() const
				{
					return (m_value);
				}

				key_type&
				key()
				{
					return (m_value.first);
				}

				key_type&
				key() const
				{
					return (m_value.first);
				}

			public:
				static node_type*
				find_uncle(base_type *tree)
				{
					if (tree->parent() == NULL)
						return NULL;

					base_type *parent = tree->parent();
					if (parent->parent() == NULL)
						return (NULL);

					base_type *grand_parent = parent->parent();
					if (grand_parent->left() == parent)
						return (static_cast<node_type*>(grand_parent->right()));
					else
						return (static_cast<node_type*>(grand_parent->left()));
				}

				static int
				black_level_of(base_type *node)
				{
					if (node)
						return (node->black_level());

					return (1);
				}

				static size_type
				size(base_type *node)
				{
					if (!node)
						return (0);

					return (size(node->left()) + size(node->right()) + 1);
				}

				static node_type*
				min(base_type *node)
				{
					while (node)
					{
						if (!node->left())
							break;

						node = node->left();
					}

					return (static_cast<node_type*>(node));
				}

				static node_type*
				max(base_type *node)
				{
					while (node)
					{
						if (!node->right())
							break;

						node = node->right();
					}

					return (static_cast<node_type*>(node));
				}

				static node_type*
				next(node_type *node)
				{
					if (node != NULL)
					{
						if (node->right() != NULL)
							return (min(node->right()));

						if (node->is_left_child())
							return (static_cast<node_type*>(node->parent()));

						base_type *next = node;
						do
						{
							next = next->parent();
						}
						while ((next != NULL) && next->is_right_child());

						if (next != NULL)
							return (static_cast<node_type*>(next->parent()));
						else
							return (NULL);
					}

					return (NULL);
				}

				static node_type*
				previous(node_type *node)
				{
					//check if the node has a left subtree
					if (node != NULL)
					{
						if (node->left() != NULL)
							return (max(node->left()));

						if (node->is_right_child())
							return (static_cast<node_type*>(node->parent()));

						base_type *previous = node;
						do
						{
							previous = previous->parent();
						}
						while (previous != NULL && previous->is_left_child());

						if (previous != NULL)
							return (static_cast<node_type*>(previous->parent()));
						else
							return (NULL);
					}

					return (NULL);
				}
		};

	template<class Key, class T, class Compare>
		class MapNormalIterator
		{

			public:
				typedef Key key_type;
				typedef T mapped_type;
				typedef ft::bidirectional_iterator_tag iterator_category;
				typedef pair<key_type, mapped_type> value_type;
				typedef ptrdiff_t difference_type;
				typedef value_type *pointer;
				typedef value_type &reference;

			private:
				typedef BaseMapNode base_node_type;
				typedef MapNode<Key, T, Compare> node_type;

			private:
				node_type *m_node;

			public:
				MapNormalIterator() :
						m_node(NULL)
				{
				}

				explicit
				MapNormalIterator(node_type *node) :
						m_node(node)
				{
				}

				explicit
				MapNormalIterator(const MapNormalIterator &other) :
						m_node(other.m_node)
				{
				}

				template<class T_, class Key_, class Compare_>
					MapNormalIterator(const MapNormalIterator<T_, Key_, Compare_> &other) :
							m_node(other.node())
					{
					}

				~MapNormalIterator()
				{
				}

				MapNormalIterator&
				operator=(const MapNormalIterator &other)
				{
					if (this != &other)
						m_node = other.m_node;

					return (*this);
				}

				MapNormalIterator&
				operator++()
				{
					m_node = node_type::next(m_node);

					return (*this);
				}

				MapNormalIterator
				operator++(int)
				{
					MapNormalIterator copy = *this;

					m_node = node_type::next(m_node);

					return (copy);
				}

				MapNormalIterator&
				operator--()
				{
					m_node = node_type::previous(m_node);

					return (*this);
				}

				MapNormalIterator
				operator--(int)
				{
					MapNormalIterator copy = *this;

					m_node = node_type::previous(m_node);

					return (copy);
				}

				reference
				operator*() const
				{
					return (m_node->value());
				}

				pointer
				operator->() const
				{
					return (&m_node->value());
				}

				node_type*
				node()
				{
					return (m_node);
				}

				node_type*
				node() const
				{
					return (m_node);
				}
		};

	template<class Key, class T, class Compare>
		inline bool
		operator==(const MapNormalIterator<Key, T, Compare> &lhs, const MapNormalIterator<Key, T, Compare> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<class Key, class T, class Compare>
		inline bool
		operator!=(const MapNormalIterator<Key, T, Compare> &lhs, const MapNormalIterator<Key, T, Compare> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
		class Map
		{
			public:
				/** The first template parameter (Key). **/
				typedef const Key key_type;

				/** The second template parameter (T). */
				typedef T mapped_type;

				/** pair<const key_type, mapped_type> */
//				typedef pair<const key_type, mapped_type> value_type;
				typedef pair<key_type, mapped_type> value_type;

				/** The third template parameter (Compare). */
				typedef Compare key_compare;

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
				typedef Alloc allocator_type;

				/** allocator_type::reference */
				typedef typename allocator_type::reference reference;

				/** allocator_type::reference */
				typedef typename allocator_type::const_reference const_reference;

				/** allocator_type::pointer */
				typedef typename allocator_type::pointer pointer;

				/** allocator_type::const_pointer */
				typedef typename allocator_type::const_pointer const_pointer;

				/** a bidirectional iterator to value_type */
				typedef MapNormalIterator<Key, T, Compare> iterator;

				/** a bidirectional iterator to const value_type */
				typedef MapNormalIterator<Key, T, Compare> const_iterator;

				/** reverse_iterator<iterator> */
				typedef ft::reverse_iterator<iterator, false> reverse_iterator;

				/** reverse_iterator<const_iterator> */
				typedef ft::reverse_iterator<const_iterator, false> const_reverse_iterator;

				/** a signed integral type, identical to: iterator_traits<iterator>::difference_type */
				typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

				/** an unsigned integral type that can represent any non-negative value of difference_type. */
				typedef size_t size_type;

			private:
				typedef BaseMapNode base_node_type;
				typedef MapNode<Key, T, Compare> node_type;
				typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;

			private:
			public:
				Compare m_compare;
				allocator_type m_allocator;
				node_allocator_type m_node_allocator;
				node_type *m_root;

			public:
				explicit
				Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
						m_compare(comp),
						m_allocator(alloc),
						m_node_allocator(m_allocator),
						m_root(NULL)
				{
				}

				template<class InputIterator>
					Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
							m_compare(comp),
							m_allocator(alloc),
							m_node_allocator(m_allocator),
							m_root(NULL)
					{
						insert_iter_impl(first, last);
					}

				Map(const Map &x) :
						m_compare(),
						m_allocator(),
						m_node_allocator(m_allocator),
						m_root(NULL)
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
					{
						clear();
						insert(x.begin(), x.end());
					}

					return (*this);
				}

				iterator
				begin()
				{
					return (iterator(node_type::min(m_root)));
				}

				const_iterator
				begin() const
				{
					return (const_iterator(node_type::min(m_root)));
				}

				iterator
				end()
				{
					return (iterator());
				}

				const_iterator
				end() const
				{
					return (const_iterator());
				}

				reverse_iterator
				rbegin()
				{
					return (reverse_iterator(iterator(node_type::max(m_root))));
				}

				const_reverse_iterator
				rbegin() const
				{
					return (reverse_iterator(const_iterator()));
				}

				reverse_iterator
				rend()
				{
					return (reverse_iterator(iterator()));
				}

				const_reverse_iterator
				rend() const
				{
					return (reverse_iterator(const_iterator(node_type::max(m_root))));
				}

				bool
				empty() const
				{
					return (m_root == NULL);
				}

				size_type
				size() const
				{
					return (node_type::size(m_root));
				}

				size_type
				max_size() const
				{
					return (m_node_allocator.max_size());
				}

				mapped_type&
				operator[](const key_type &k)
				{
					return ((*((this->insert(make_pair(k, mapped_type()))).first)).second);
				}

				pair<iterator, bool>
				insert(const value_type &val)
				{
					pair<node_type*, bool> inserted = insert_impl(val);

					return (make_pair(iterator(inserted.first), inserted.second));
				}

				iterator
				insert(iterator position, const value_type &val)
				{
					(void)position; /* discarded hint */

					return (insert(val).first);
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
					delete_impl(position.node());
				}

				size_type
				erase(const key_type &k)
				{
					iterator position = find(k);

					if (position != end())
					{
						erase(position);
						return (1);
					}

					return (0);
				}

				void
				erase(iterator first, iterator last)
				{
					while (first != last)
						erase(first++);
				}

				void
				swap(Map &x)
				{
					ft::swap(m_root, x.m_root);
				}

				void
				clear()
				{
					erase(begin(), end());
				}

				key_compare
				key_comp() const
				{
					return (m_compare);
				}

				value_compare
				value_comp() const
				{
					return (value_compare());
				}

				iterator
				find(const key_type &k)
				{
					node_type *node = m_root;

					while (node)
					{
						const key_type &b = node->key();

						if (do_compare(k, b))
							node = static_cast<node_type*>(node->left());
						else if (are_keys_equal(k, b))
							return (iterator(node));
						else
							node = static_cast<node_type*>(node->right());
					}

					return (end());
				}

				const_iterator
				find(const key_type &k) const
				{
					node_type *node = m_root;

					while (node)
					{
						const key_type &b = node->key();

						if (do_compare(k, b))
							node = static_cast<node_type*>(node->left());
						else if (are_keys_equal(k, b))
							return (iterator(node));
						else
							node = static_cast<node_type*>(node->right());
					}

					return (end());
				}

				size_type
				count(const key_type &k) const
				{
					return (find(k) != end() ? 1 : 0);
				}

				iterator
				lower_bound(const key_type &k)
				{
					iterator it = begin();

					while (key_comp()(it->first, k) && it != end())
						it++;

					return (it);
				}

				const_iterator
				lower_bound(const key_type &k) const
				{
					const_iterator it = begin();

					while (key_comp()(it->first, k) && it != end())
						it++;

					return (it);
				}

				iterator
				upper_bound(const key_type &k)
				{
					iterator it = lower_bound(k);

					if (it != end() && !(key_comp()(k, it->first)))
						it++;

					return (it);
				}

				const_iterator
				upper_bound(const key_type &k) const
				{
					const_iterator it = lower_bound(k);

					if (it != end() && !(key_comp()(k, it->first)))
						it++;

					return (it);
				}

				pair<const_iterator, const_iterator>
				equal_range(const key_type &k) const
				{
					return (make_pair(lower_bound(k), upper_bound(k)));
				}

				pair<iterator, iterator>
				equal_range(const key_type &k)
				{
					return (make_pair(lower_bound(k), upper_bound(k)));
				}

			public:
				void
				dump()
				{
					dump(*m_root);
				}

				void
				dump(node_type &n, int indent = 0)
				{
					for (int i = 0; i < indent; i++)
						std::cout << '\t';

					std::cout << (n.black_level() == 0 ? "RED" : "BLACK") << ": " << n.value().first << std::endl;

					if (n.left())
						dump(static_cast<node_type&>(*n.left()), indent + 1);
					if (n.right())
						dump(static_cast<node_type&>(*n.right()), indent + 1);
				}

			private:
				bool
				do_compare(const key_type &a, const key_type &b)
				{
					return (m_compare(a, b));
				}

				bool
				are_keys_equal(const key_type &a, const key_type &b)
				{
					return (!m_compare(a, b) && !m_compare(b, a));
				}

				bool
				do_compare(const key_type &a, const key_type &b) const
				{
					return (m_compare(a, b));
				}

				bool
				are_keys_equal(const key_type &a, const key_type &b) const
				{
					return (!m_compare(a, b) && !m_compare(b, a));
				}

				template<class InputIterator>
					void
					insert_iter_impl(InputIterator first, InputIterator last)
					{
						while (first != last)
							insert_impl(*first++);
					}

				pair<node_type*, bool>
				insert_impl(const value_type &val)
				{
					if (m_root == NULL)
					{
						m_root = new node_type(val);
						m_root->black_level() = 1;
						return (make_pair(m_root, true));
					}

					return (insert_impl(m_root, val));
				}

				pair<node_type*, bool>
				insert_impl(node_type *root, const value_type &val)
				{
					if (val.first < root->key())
					{
						if (root->left() == NULL)
						{
							node_type *node = new node_type(val);

							root->left() = node;
							node->parent() = root;

							fix_double_red(node);

							return (make_pair(node, true));
						}
						else
						{
							return (insert_impl(static_cast<node_type*>(root->left()), val));
						}
					}
					else if (are_keys_equal(val.first, root->key()))
					{
						return (make_pair(root, false));
					}
					else
					{
						if (root->right() == NULL)
						{
							node_type *node = new node_type(val);

							root->right() = node;
							node->parent() = root;

							fix_double_red(node);

							return (make_pair(node, true));
						}
						else
						{
							return (insert_impl(static_cast<node_type*>(root->right()), val));
						}
					}
				}

				void
				fix_double_red(base_node_type *node)
				{
					if (node->parent() != NULL)
					{
						if (node->parent()->black_level() > 0)
							return;

						if (node->parent()->parent() == NULL)
						{
							node->parent()->black_level() = 1;
							return;
						}

						node_type *uncle = node_type::find_uncle(node);
						if (node_type::black_level_of(uncle) == 0)
						{
							uncle->black_level() = 1;
							node->parent()->black_level() = 1;
							node->parent()->parent()->black_level() = 0;

							fix_double_red(node->parent()->parent());
						}
						else
						{
							if (node->is_left_child() && !node->parent()->is_left_child())
							{
								single_rotate_right(node->parent());
								node = node->right();
							}
							else if (!node->is_left_child() && node->parent()->is_left_child())
							{
								single_rotate_left(node->parent());
								node = node->left();
							}

							if (node->is_left_child())
							{
								single_rotate_right(node->parent()->parent());
								node->parent()->black_level() = 1;
								node->parent()->right()->black_level() = 0;
							}
							else
							{
								single_rotate_left(node->parent()->parent());
								node->parent()->black_level() = 1;
								node->parent()->left()->black_level() = 0;
							}
						}
					}
					else
					{
						if (node->black_level() == 0)
							node->black_level() = 1;
					}
				}

				base_node_type*
				single_rotate_left(base_node_type *node)
				{
					base_node_type *a = node;
					base_node_type *b = node->right();

//					node_type *t1 = a->left();
					base_node_type *t2 = b->left();
//					node_type *t3 = b->right();

					if (t2 != NULL)
						t2->parent() = a;

					b->parent() = a->parent();

					if (m_root == a)
						m_root = static_cast<node_type*>(b);
					else
					{
						if (a->is_left_child())
							a->parent()->left() = b;
						else
							a->parent()->right() = b;
					}

					b->left() = a;
					a->parent() = b;
					a->right() = t2;

					return (b);
				}

				base_node_type*
				single_rotate_right(base_node_type *node)
				{
					base_node_type *a = node->left();
					base_node_type *b = node;

//					node_type *t1 = a->left();
					base_node_type *t2 = a->right();
//					node_type *t3 = b->right();

					if (t2 != NULL)
						t2->parent() = b;

					a->parent() = b->parent();
					if (m_root == b)
						m_root = static_cast<node_type*>(a);
					else
					{
						if (b->is_left_child())
							b->parent()->left() = a;
						else
							b->parent()->right() = a;
					}

					a->right() = b;
					b->parent() = a;
					b->left() = t2;

					return (a);
				}

				void
				fix_left_null(base_node_type *node)
				{
					base_node_type null_leaf;
					null_leaf.black_level() = 2;
					null_leaf.parent() = node;

					node->left() = &null_leaf;

					fix_extra_black_child(node, true);

					if (null_leaf.is_left_child())
						null_leaf.parent()->left() = NULL;

					if (null_leaf.is_right_child())
						null_leaf.parent()->right() = NULL;

//					node->left() = NULL;
//					fix_extra_black_child(node, true);
				}

				void
				fix_right_null(base_node_type *node)
				{

					base_node_type null_leaf;
					null_leaf.black_level() = 2;
					null_leaf.parent() = node;

					node->right() = &null_leaf;

					fix_extra_black_child(node, false);

					if (null_leaf.is_left_child())
						null_leaf.parent()->left() = NULL;

					if (null_leaf.is_right_child())
						null_leaf.parent()->right() = NULL;

//					node->right() = NULL;
//					fix_extra_black_child(node, false);
				}

				void
				fix_extra_black_child(base_node_type *parent_node, bool is_left_child)
				{
					base_node_type *sibling, *double_black_node;

					if (is_left_child)
					{
						sibling = parent_node->right();
						double_black_node = parent_node->left();
					}
					else
					{
						sibling = parent_node->left();
						double_black_node = parent_node->right();
					}

					if (node_type::black_level_of(sibling) > 0 && node_type::black_level_of(sibling->left()) > 0 && node_type::black_level_of(sibling->right()) > 0)
					{
						sibling->black_level() = 0;

						if (double_black_node != NULL)
						{
							double_black_node->black_level() = 1;
						}

						if (parent_node->black_level() == 0)
						{
							parent_node->black_level() = 1;
						}
						else
						{
							parent_node->black_level() = 2;
							fix_extra_black(parent_node);
						}
					}
					else if (node_type::black_level_of(sibling) == 0)
					{
						if (is_left_child)
						{
							base_node_type *new_parent = single_rotate_left(parent_node);
							new_parent->black_level() = 1;
							new_parent->left()->black_level() = 0;
							fix_extra_black(new_parent->left()->left());
						}
						else
						{
							base_node_type *new_parent = single_rotate_right(parent_node);
							new_parent->black_level() = 1;
							new_parent->right()->black_level() = 0;
							fix_extra_black(new_parent->right()->right());
						}
					}
					else if (is_left_child && node_type::black_level_of(sibling->right()) > 0)
					{
						base_node_type *new_sibling = single_rotate_right(sibling);
						new_sibling->black_level() = 1;
						new_sibling->right()->black_level() = 0;
						fix_extra_black_child(parent_node, is_left_child);
					}
					else if (!is_left_child && node_type::black_level_of(sibling->left()) > 0)
					{
						base_node_type *new_sibling = single_rotate_left(sibling);
						new_sibling->black_level() = 1;
						new_sibling->left()->black_level() = 0;
						fix_extra_black_child(parent_node, is_left_child);
					}
					else if (is_left_child)
					{
						int old_parent_black_level = parent_node->black_level();
						base_node_type *new_parent = single_rotate_left(parent_node);

						if (old_parent_black_level == 0)
						{
							new_parent->black_level() = 0;
							new_parent->left()->black_level() = 1;
						}

						new_parent->right()->black_level() = 1;
						if (new_parent->left()->left() != NULL)
						{
							new_parent->left()->left()->black_level() = 1;
						}
					}
					else
					{
						int old_parent_black_level = parent_node->black_level();
						base_node_type *new_parent = single_rotate_right(parent_node);

						if (old_parent_black_level == 0)
						{
							new_parent->black_level() = 0;
							new_parent->right()->black_level() = 1;
						}

						new_parent->left()->black_level() = 1;
						if (new_parent->right()->right() != NULL)
						{
							new_parent->right()->right()->black_level() = 1;
						}
					}
				}

				void
				fix_extra_black(base_node_type *node)
				{
					if (node->black_level() > 1)
					{
						if (node->parent() == NULL)
						{
							node->black_level() = 1;
						}
						else if (node->parent()->left() == node)
						{
							fix_extra_black_child(node->parent(), true);
						}
						else
						{
							fix_extra_black_child(node->parent(), false);
						}
					}
				}

				void
				delete_impl(node_type *node)
				{
					if (node == NULL)
						return;

					bool left_child = false;
					if (node->parent() != NULL)
					{
						left_child = node->parent()->left() == node;
					}

					bool need_fix = node->black_level() > 0;
					if (node->left() == NULL && node->right() == NULL)
					{
						if (left_child && node->parent() != NULL)
						{
//							delete node->parent()->left();
							node->parent()->left() = NULL;

							if (need_fix)
							{
								fix_left_null(node->parent());
							}
						}
						else if (node->parent() != NULL)
						{
//							delete node->parent()->right();
							node->parent()->right() = NULL;

							if (need_fix)
							{
								fix_right_null(node->parent());
							}
						}
						else
						{
//							delete m_root;
							m_root = NULL;
						}
					}
					else if (node->left() == NULL)
					{
						if (node->parent() != NULL)
						{
							if (left_child)
							{
//								delete node->parent()->left();
								node->parent()->left() = node->right();

								if (need_fix)
								{
									node->parent()->left()->black_level() += 1;
									fix_extra_black(node->parent()->left());
								}
							}
							else
							{
//								delete node->parent()->right();
								node->parent()->right() = node->right();

								if (need_fix)
								{
									node->parent()->right()->black_level() += 1;
									fix_extra_black(node->parent()->right());
								}
							}

							node->right()->parent() = node->parent();
						}
						else
						{
							m_root = static_cast<node_type*>(node->right());

//							delete m_root->parent();
							m_root->parent() = NULL;

							if (m_root->black_level() == 0)
							{
								m_root->black_level() = 1;
							}
						}
					}
					else if (node->right() == NULL)
					{
						if (node->parent() != NULL)
						{
							if (left_child)
							{
								node->parent()->left() = node->left();

								if (need_fix)
								{
									node->parent()->left()->black_level() += 1;
									fix_extra_black(node->parent()->left());
								}
							}
							else
							{
								node->parent()->right() = node->left();

								if (need_fix)
								{
									node->parent()->right()->black_level() += 1;
									fix_extra_black(node->parent()->left());
								}
							}

							node->left()->parent() = node->parent();
						}
						else
						{
							m_root = static_cast<node_type*>(node->left());
							m_root->parent() = NULL;

							if (m_root->black_level() == 0)
							{
								m_root->black_level() = 1;
							}
						}
					}
					else // node->left() != NULL && node->right() != NULL
					{
						base_node_type *tmp = node->left();

						while (tmp->right() != NULL)
							tmp = tmp->right();

						node->value().second = static_cast<node_type*>(tmp)->value().second;

						bool need_fix = tmp->black_level() > 0;

						if (tmp->left() == NULL)
						{
							if (tmp->parent() != node)
							{
								tmp->parent()->right() = NULL;

								if (need_fix)
								{
									fix_right_null(tmp->parent());
								}
							}
							else
							{
								node->left() = NULL;

								if (need_fix)
								{
									fix_left_null(tmp->parent());
								}
							}
						}
						else
						{
							if (tmp->parent() != node)
							{
								tmp->parent()->right() = tmp->left();
								tmp->left()->parent() = tmp->parent();

								if (need_fix)
								{
									tmp->left()->black_level() += 1;
									fix_extra_black(tmp->left());
								}
							}
							else
							{
								node->left() = tmp->left();
								tmp->left()->parent() = node;

								if (need_fix)
								{
									tmp->left()->black_level() += 1;
									fix_extra_black(tmp->left());
								}
							}
						}

						tmp = tmp->parent();
					}
				}
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
