/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:03:30 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/19 18:03:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP_
# define REDBLACKTREE_HPP_

#include <Algorithm.hpp>
#include <bits/allocator.h>
#include <Function.hpp>
#include <Functional.hpp>
#include <Iterator.hpp>
#include <Utility.hpp>
#include <cstddef>
#include <iostream>
#include <cassert>
#include <cstdio>

namespace ft
{
	enum RedBlackTreeNodeColor
	{
		UNCOLORED = -1,
		RED = 0,
		BLACK = 1,
	};

	class RedBlackTreeNodeBase
	{
		public:
			typedef RedBlackTreeNodeBase base_type;
			typedef const RedBlackTreeNodeBase base_const_type;
			typedef RedBlackTreeNodeColor color_type;

		private:
			base_type *m_parent;
			base_type *m_left;
			base_type *m_right;
			color_type m_color;

		public:
			RedBlackTreeNodeBase() :
					m_parent(NULL),
					m_left(NULL),
					m_right(NULL),
					m_color(UNCOLORED)
			{
			}

			base_type*
			without_const_base() const
			{
				return (const_cast<base_type*>(this));
			}

			inline base_type*&
			right()
			{
				return (m_right);
			}

			inline base_type*
			right() const
			{
				return (m_right);
			}

			inline base_type*&
			left()
			{
				return (m_left);
			}

			inline base_type*
			left() const
			{
				return (m_left);
			}

			inline base_type*&
			parent()
			{
				return (m_parent);
			}

			inline base_type*
			parent() const
			{
				return (m_parent);
			}

			inline color_type&
			color()
			{
				return (m_color);
			}

			inline color_type
			color() const
			{
				return (m_color);
			}

			inline bool
			is_left_child() const
			{
				if (m_parent)
					return (m_parent->m_left == this);

				return (true);
			}

			inline bool
			is_right_child() const
			{
				if (m_parent)
					return (m_parent->m_right == this);

				return (true);
			}

		private:
			static base_type*
			min_impl(base_type *node)
			{
				if (node)
				{
					while (node->left())
						node = node->left();
				}

				return (node);
			}

			static base_type*
			max_impl(base_type *node)
			{
				if (node)
				{
					while (node->right())
						node = node->right();
				}

				return (node);
			}

			static base_type*
			next_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				if (node->right() != NULL)
					return (min_impl(node->right()));

				return (upUntilLeftChild_impl(node));
			}

			static base_type*
			previous_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				if (node->left() != NULL)
					return (max_impl(node->left()));

				return (upUntilRightChild_impl(node));
			}

			static base_type*
			upUntilLeftChild_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				while (node->parent() != NULL && node->parent()->color() != UNCOLORED && node != node->parent()->left())
					node = node->parent();

				return (node->parent());
			}

			static base_type*
			upUntilRightChild_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				while (node->parent() != NULL && node->parent()->color() != UNCOLORED && node != node->parent()->right())
					node = node->parent();

				return (node->parent());
			}

			static size_t
			size_impl(base_type *node)
			{
				if (!node)
					return (0);

				return (size_impl(node->left()) + size_impl(node->right()) + 1);
			}

			static base_type*
			uncle_impl(base_type *node)
			{
				base_type *parent = node->m_parent;
				base_type *grand = parent->m_parent;

				if (grand->m_left == parent)
					return (grand->m_right);
				else
					return (grand->m_left);
			}

			static color_type
			color_impl(base_type *node)
			{
				if (node == NULL)
					return (BLACK);

				return (node->m_color);
			}

			static bool
			has_red_child_impl(base_type *node)
			{
				if (node != NULL)
				{
					if (color_impl(node->left()) == RED)
						return (true);

					if (color_impl(node->right()) == RED)
						return (true);
				}

				return (false);
			}

			static base_type*
			sibling_impl(base_type *node)
			{
				if (node != NULL)
				{
					base_type *parent = node->parent();

					if (parent != NULL)
					{
						if (parent->left() == node)
							return (parent->right());
						else
							return (parent->left());
					}
				}

				return (NULL);
			}

		public:
			static base_type*
			min(base_type *node)
			{
				return (min_impl(node));
			}

			static base_const_type*
			min(base_const_type *node)
			{
				return (min_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			max(base_type *node)
			{
				return (max_impl(node));
			}

			static base_const_type*
			max(base_const_type *node)
			{
				return (max_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			next(base_type *node)
			{
				return (next_impl(node));
			}

			static base_const_type*
			next(base_const_type *node)
			{
				return (next_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			previous(base_type *node)
			{
				return (previous_impl(node));
			}

			static base_const_type*
			previous(base_const_type *node)
			{
				return (previous_impl(const_cast<base_type*>(node)));
			}

			static size_t
			size(base_type *node)
			{
				return (size_impl(node));
			}

			static size_t
			size(base_const_type *node)
			{
				return (size_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			uncle(base_type *node)
			{
				return (uncle_impl(node));
			}

			static base_const_type*
			uncle(base_const_type *node)
			{
				return (uncle_impl(const_cast<base_type*>(node)));
			}

			static color_type
			color(base_type *node)
			{
				return (color_impl(node));
			}

			static color_type
			color(base_const_type *node)
			{
				return (color_impl(const_cast<base_type*>(node)));
			}

			static bool
			has_red_child(base_type *node)
			{
				return (has_red_child_impl(node));
			}

			static bool
			has_red_child(base_const_type *node)
			{
				return (has_red_child_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			sibling(base_type *node)
			{
				return (sibling_impl(node));
			}

			static base_const_type*
			sibling(base_const_type *node)
			{
				return (sibling_impl(const_cast<base_type*>(node)));
			}

	};

	template<class T>
		class RedBlackTreeNode :
				public RedBlackTreeNodeBase
		{
			public:
				typedef RedBlackTreeNodeBase::base_type base_type;
				typedef RedBlackTreeNodeBase::base_const_type base_const_type;

				typedef T value_type;
				typedef RedBlackTreeNode<value_type> node_type;
				typedef const RedBlackTreeNode<value_type> node_const_type;

			private:
				value_type m_value;

			public:
				RedBlackTreeNode(const value_type &value) :
						RedBlackTreeNodeBase(),
						m_value(value)
				{
				}

				base_type*
				without_const() const
				{
					return (const_cast<base_type*>(this));
				}

				inline value_type&
				value()
				{
					return (m_value);
				}
		};

	template<typename T>
		struct RedBlackTreeIterator
		{
			public:
				typedef T value_type;
				typedef T &reference;
				typedef T *pointer;
				typedef bidirectional_iterator_tag iterator_category;
				typedef ptrdiff_t difference_type;

			private:
				typedef RedBlackTreeIterator<T> iterator_type;
				typedef RedBlackTreeNodeBase node_base_type;
				typedef RedBlackTreeNode<T> node_type;

			private:
				node_base_type *m_node;

			public:
				RedBlackTreeIterator() :
						m_node()
				{
				}

				RedBlackTreeIterator(node_base_type *node) :
						m_node(node)
				{
				}

				template<typename U>
					RedBlackTreeIterator(const RedBlackTreeIterator<U> &other) :
							m_node(other.node())
					{
					}

				~RedBlackTreeIterator()
				{
				}

				RedBlackTreeIterator&
				operator=(const RedBlackTreeIterator &other)
				{
					if (this != &other)
						m_node = other.m_node;

					return (*this);
				}

				iterator_type&
				operator++()
				{
					m_node = RedBlackTreeNodeBase::next(m_node);

					return (*this);
				}

				iterator_type
				operator++(int)
				{
					iterator_type copy = *this;

					m_node = RedBlackTreeNodeBase::next(m_node);

					return (copy);
				}

				iterator_type&
				operator--()
				{
					m_node = RedBlackTreeNodeBase::previous(m_node);

					return (*this);
				}

				iterator_type
				operator--(int)
				{
					iterator_type copy = *this;

					m_node = RedBlackTreeNodeBase::previous(m_node);

					return (copy);
				}

				reference
				operator*() const
				{
					return (node()->value());
				}

				pointer
				operator->() const
				{
					return (&node()->value());
				}

				node_base_type*
				base_node()
				{
					return (m_node);
				}

				node_type*
				node()
				{
					return (static_cast<node_type*>(m_node));
				}

				node_base_type*
				base_node() const
				{
					return (m_node);
				}

				node_type*
				node() const
				{
					return (static_cast<node_type*>(m_node));
				}

				template<typename U>
					friend bool
					operator==(const RedBlackTreeIterator<U> &x, const RedBlackTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const RedBlackTreeIterator<U> &x, const RedBlackTreeIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const RedBlackTreeIterator<T> &x, const RedBlackTreeIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const RedBlackTreeIterator<T> &x, const RedBlackTreeIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		struct RedBlackTreeConstIterator
		{
			public:
				typedef T value_type;
				typedef const T &reference;
				typedef const T *pointer;
				typedef bidirectional_iterator_tag iterator_category;
				typedef ptrdiff_t difference_type;

			private:
				typedef RedBlackTreeIterator<T> iterator_type;
				typedef RedBlackTreeConstIterator<T> const_iterator_type;

				typedef RedBlackTreeNodeBase node_base_type;
				typedef RedBlackTreeNode<T> node_type;
				typedef const RedBlackTreeNodeBase node_base_const_type;
				typedef const RedBlackTreeNode<T> node_const_type;

			private:
				node_base_const_type *m_node;

			public:
				RedBlackTreeConstIterator() :
						m_node()
				{
				}

				RedBlackTreeConstIterator(node_base_const_type *node) :
						m_node(node)
				{
				}

				RedBlackTreeConstIterator(const iterator_type &it) :
						m_node(it.base_node())
				{
				}

				const_iterator_type&
				operator++()
				{
					m_node = RedBlackTreeNodeBase::next(m_node);

					return (*this);
				}

				const_iterator_type
				operator++(int)
				{
					const_iterator_type copy = *this;

					m_node = RedBlackTreeNodeBase::next(m_node);

					return (copy);
				}

				const_iterator_type&
				operator--()
				{
					m_node = RedBlackTreeNodeBase::previous(m_node);

					return (*this);
				}

				const_iterator_type
				operator--(int)
				{
					const_iterator_type copy = *this;

					m_node = RedBlackTreeNodeBase::previous(m_node);

					return (copy);
				}

				reference
				operator*() const
				{
					return (node()->value());
				}

				pointer
				operator->() const
				{
					return (&node()->value());
				}

				iterator_type
				remove_const() const
				{
					return (iterator_type(const_cast<node_base_type>(m_node)));
				}

				node_base_const_type*
				base_node()
				{
					return (m_node);
				}

				node_const_type*
				node()
				{
					return (static_cast<node_const_type*>(m_node));
				}

				node_base_const_type*
				base_node() const
				{
					return (m_node);
				}

				node_const_type*
				node() const
				{
					return (static_cast<node_const_type*>(m_node));
				}

				template<typename U>
					friend bool
					operator==(const RedBlackTreeConstIterator<U> &x, const RedBlackTreeConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const RedBlackTreeConstIterator<U> &x, const RedBlackTreeConstIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const RedBlackTreeConstIterator<T> &x, const RedBlackTreeConstIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const RedBlackTreeConstIterator<T> &x, const RedBlackTreeConstIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<class Key, class T/*, class Compare, class Alloc*/>
		class RedBlackTree
		{
				typedef less<Key> Compare;
				typedef std::allocator<pair<const Key, T> > Alloc;

			public:
				typedef Key key_type;
				typedef T mapped_type;
				typedef pair<key_type, mapped_type> value_type;
				typedef Compare key_compare;
				typedef Alloc allocator_type;
				typedef typename allocator_type::reference reference;
				typedef typename allocator_type::const_reference const_reference;
				typedef typename allocator_type::pointer pointer;
				typedef typename allocator_type::const_pointer const_pointer;
				typedef RedBlackTreeIterator<value_type> iterator;
				typedef RedBlackTreeConstIterator<value_type> const_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
				typedef size_t size_type;

			private:
				typedef RedBlackTreeNodeBase node_base_type;
				typedef RedBlackTreeNode<value_type> node_type;
				typedef const RedBlackTreeNodeBase node_base_const_type;
				typedef const RedBlackTreeNode<value_type> node_const_type;
				typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;
				typedef enum
				{
					LEFTLEFT,
					LEFTRIGHT,
					RIGHTLEFT,
					RIGHTRIGHT
				} relation_type;

			private:
				Compare m_compare;
				allocator_type m_allocator;
				node_allocator_type m_node_allocator;
				node_base_type m_head;
				node_type *m_root;

			public:
				RedBlackTree(const key_compare &comp, const allocator_type &alloc) :
						m_compare(comp),
						m_allocator(alloc),
						m_node_allocator(m_allocator),
						m_head(),
						m_root(NULL)
				{
				}

				~RedBlackTree()
				{
				}

				RedBlackTree&
				operator=(const RedBlackTree &x)
				{
					if (this != &x)
					{
						clear();
						insert(x.begin(), x.end());
					}

					return (*this);
				}

				node_base_type*
				begin()
				{
					return (m_root ? node_base_type::min(m_root) : &m_head);
				}

				node_base_const_type*
				begin() const
				{
					return (m_root ? node_base_type::min(m_root) : &m_head);
				}

				node_base_type*
				end()
				{
					return (&m_head);
				}

				node_base_const_type*
				end() const
				{
					return (&m_head);
				}

				bool
				empty() const
				{
					return (m_root == NULL);
				}

				size_type
				size() const
				{
					return (node_base_type::size(m_root));
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

				void
				unlink_head()
				{
					if (m_root)
						m_root->parent() = NULL;
				}

				void
				link_head()
				{
					if (m_root)
						m_root->parent() = &m_head;
				}

				pair<node_type*, bool>
				insert(const value_type &val)
				{
					unlink_head();

					pair<node_type*, bool> pr = insert_impl(val);

					link_head();

					return (pr);
				}

				void
				erase(node_base_type *node)
				{
					unlink_head();

					delete_impl(node);

					link_head();
				}

				size_type
				erase(const key_type &k)
				{
					node_base_type *node = find(k);

					if (node != end())
					{
						erase(node);
						return (1);
					}

					return (0);
				}

				void
				erase(node_base_type *first, node_base_type *last)
				{
					node_base_type *node = first;

					while (first != last)
					{
						node_base_type *node = first;
						first = node_base_type::next(first);
						std::cout << "erasing: " << cast(node)->value().first << " (" << node << ")" << std::endl;
						erase(node);
					}
				}

				void
				swap(RedBlackTree &x);

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

				node_base_type*
				find(const key_type &k)
				{
					return (find_impl(k));
				}

				node_base_const_type*
				find(const key_type &k) const
				{
					return (remove_const()->find_impl(k));
				}

				size_type
				count(const key_type &k) const
				{
					return (find(k) != end() ? 1 : 0);
				}

				node_base_type*
				lower_bound(const key_type &k)
				{
					return (lower_bound_impl(k));
				}

				node_base_const_type*
				lower_bound(const key_type &k) const
				{
					return (remove_const()->lower_bound_impl(k));
				}

				node_base_type*
				upper_bound(const key_type &k)
				{
					return (upper_bound_impl(k));
				}

				node_base_const_type*
				upper_bound(const key_type &k) const
				{
					return (remove_const()->upper_bound_impl(k));
				}

				pair<node_base_type, node_base_type>
				equal_range(const key_type &k)
				{
					return (equal_range(k));
				}

				pair<node_base_const_type, node_base_const_type>
				equal_range(const key_type &k) const
				{
					return (remove_const()->equal_range(k));
				}

			private:
				inline RedBlackTree*
				remove_const() const
				{
					return (static_cast<RedBlackTree*>(this));
				}

				inline node_type*
				cast(node_base_type *node)
				{
					return (static_cast<node_type*>(node));
				}

				inline node_const_type*
				cast(node_base_const_type *node) const
				{
					return (const_cast<node_const_type*>(node));
				}

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

				node_type*
				create_node(node_base_type *parent, const value_type &val)
				{
					node_type *node = m_node_allocator.allocate(1);
					new (node) node_type(val);

					node->parent() = parent;

					if (parent == NULL)
						node->color() = BLACK;
					else
						node->color() = RED;

					return (node);
				}

				void
				destroy_node(node_base_type *node)
				{
					m_node_allocator.deallocate(cast(node), 1);
				}

				pair<node_type*, bool>
				insert_impl(const value_type &val)
				{
					unlink_head();

					pair<node_type*, bool> result = insert_impl(m_root, val);

					link_head();

					return (result);
				}

				pair<node_type*, bool>
				insert_impl(node_type *node, const value_type &val)
				{
					if (m_root == NULL)
					{
						m_root = create_node(NULL, val);
						return (make_pair(m_root, true));
					}

					if (are_keys_equal(val.first, node->value().first))
						return (make_pair(node, false));

					bool is_left = do_compare(val.first, node->value().first);
					node_type *child = cast(is_left ? node->left() : node->right());

					if (child)
						return (insert_impl(child, val));

					child = create_node(node, val);

					if (is_left)
						node->left() = child;
					else
						node->right() = child;

					fix_tree(child);
					find_root();

					return (make_pair(child, true));
				}

				relation_type
				get_relation_case(node_base_type *child, node_base_type *parent, node_base_type *grand)
				{
					if (parent == grand->left())
					{
						if (child == parent->left())
							return (LEFTLEFT);
						else
							return (LEFTRIGHT);
					}
					else
					{
						if (child == parent->right())
							return (RIGHTRIGHT);
						else
							return (RIGHTLEFT);
					}
				}

				relation_type
				sibling_case(node_base_type *sibling)
				{
					if (sibling == sibling->parent()->left())
					{
						if (node_base_type::color(sibling->left()) == RED)
							return (LEFTLEFT);
						else
							return (LEFTRIGHT);
					}
					else
					{
						if (node_base_type::color(sibling->right()) == RED)
							return (RIGHTRIGHT);
						else
							return (RIGHTLEFT);
					}
				}

				void
				fix_tree(node_base_type *node)
				{
					node_base_type *parent = node->parent();
					if (parent == NULL)
					{
						node->color() = BLACK;
						return;
					}

					if (node->color() == RED && parent->color() == RED)
					{
						node_base_type *grand = parent->parent();
						node_base_type *uncle = node_base_type::uncle(node);

						if (uncle != NULL && uncle->color() == RED)
						{
							parent->color() = BLACK;
							uncle->color() = BLACK;
							if (grand->parent() != NULL)
								grand->color() = RED;

							fix_tree(grand);
						}
						else
						{
							relation_type relation = get_relation_case(node, parent, grand);
							switch (relation)
							{
								case LEFTLEFT:
								{
									parent->color() = BLACK;
									grand->color() = RED;

									rotation(parent, grand);

									break;
								}

								case LEFTRIGHT:
								{
									node->color() = BLACK;
									grand->color() = RED;

									rotation(node, parent);
									rotation(node, grand);

									break;
								}

								case RIGHTLEFT:
								{
									node->color() = BLACK;
									grand->color() = RED;

									rotation(node, parent);
									rotation(node, grand);

									break;
								}

								case RIGHTRIGHT:
								{
									parent->color() = BLACK;
									grand->color() = RED;

									rotation(parent, grand);

									break;
								}
							}
						}
					}
				}

				void
				rotation(node_base_type *child, node_base_type *parent)
				{
					node_base_type *grand = parent->parent();

					if (grand != NULL)
					{
						if (grand->left() == parent)
							grand->left() = child;
						else
							grand->right() = child;
					}

					if (child == parent->left())
					{
						if (child->right() != NULL)
							child->right()->parent() = parent;

						parent->left() = child->right();
						child->right() = parent;
					}
					else
					{
						if (child->left() != NULL)
							child->left()->parent() = parent;

						parent->right() = child->left();
						child->left() = parent;
					}

					child->parent() = grand;
					parent->parent() = child;
				}

				void
				rotation_no_color(node_base_type *child, node_base_type *parent)
				{
					rotation(child, parent);
					ft::swap(child->color(), parent->color());
//					node_base_type::color_type color = child->color;
//					child->color = parent->color;
//					parent->color = color;
				}

				void
				find_root()
				{
					if (m_root != NULL)
					{
						while (m_root->parent() != NULL)
							m_root = cast(m_root->parent());
					}
				}

				void
				delete_impl(node_base_type *node)
				{
					if (m_root == NULL || node == NULL)
						return;

					unlink_head();

					pair<bool, pair<node_base_type*, node_base_type*> > to_fix = delete_node_impl(node);
					/* return: <have to fix, <parent, sibling> */

					if (to_fix.first && m_root != NULL)
					{
						node_base_type *parent = to_fix.second.first;
						node_base_type *sibling = to_fix.second.second;

						if (parent == NULL)
							m_root->color() = BLACK;
						else if (sibling != NULL)
							fix_delete(parent, sibling);
					}

					link_head();
				}

				pair<bool, pair<node_base_type*, node_base_type*> >
				delete_node_impl(node_base_type *node)
				{
					if (!node)
						return (make_pair(false, make_pair((node_base_type*)NULL, (node_base_type*)NULL)));

					node_base_type *parent = node->parent();
					if (node->left() != NULL && node->right() != NULL)
					{
						node_base_type *sucessor = node_base_type::next(node);
						if (sucessor == NULL)
							assert(!"invalid tree state");

						// do delete, around line 593
						cast(node)->value() = cast(sucessor)->value();
						return (delete_node_impl(sucessor));
					}
					else
					{
						pair<bool, pair<node_base_type*, node_base_type*> > result;

						if (node->left() != NULL)
						{
							if (node->color() == RED || node->left()->color() == RED)
							{
								node->color() = BLACK;
								result = make_pair(false, make_pair((node_base_type*)NULL, (node_base_type*)NULL));
							}
							else
								result = make_pair(true, make_pair(parent, node_base_type::sibling(node)));

							node_base_type *child = node->left();
							// do delete, around line 614
							cast(node)->value() = cast(child)->value();

							node->left() = child->left();
							if (child->left() != NULL)
								child->left()->parent() = node;

							node->right() = child->right();
							if (child->right() != NULL)
								child->right()->parent() = node;

							destroy_node(child);
						}
						else if (node->right() != NULL)
						{
							if (node->color() == RED || node->right()->color() == RED)
							{
								node->color() = BLACK;
								result = make_pair(false, make_pair((node_base_type*)NULL, (node_base_type*)NULL));
							}
							else
								result = make_pair(true, make_pair(parent, node_base_type::sibling(node)));

							node_base_type *child = node->right();
							// do delete, around linge 644

							cast(node)->value() = cast(child)->value();

							node->left() = child->left();
							if (child->left() != NULL)
								child->left()->parent() = node;

							node->right() = child->right();
							if (child->right() != NULL)
								child->right()->parent() = node;

							destroy_node(node);
						}
						else
						{
							if (node->color() == RED)
							{
								node->color() = BLACK;
								result = make_pair(false,make_pair((node_base_type*)NULL, (node_base_type*)NULL));
							}
							else
								result = make_pair(true, make_pair(parent, node_base_type::sibling(node)));

							if (parent != NULL)
							{
								if (node == parent->left())
									parent->left() = NULL;
								else
									parent->right() = NULL;
							}

							// do delete, around line 676

							destroy_node(node);

							if (parent == NULL)
								m_root = NULL;
						}

						find_root();

						return (result);
					}
				}

				void
				fix_delete(node_base_type *parent, node_base_type *sibling)
				{
					if (sibling->color() == BLACK)
					{
						if (node_base_type::has_red_child(sibling)) /* Case A: If sibling is BLACK and at least one of sibling's children is RED */
						{
							switch (sibling_case(sibling))
							{
								case LEFTLEFT:
								{
									sibling->left()->color() = BLACK;

									rotation_no_color(sibling, parent);

									break;
								}

								case LEFTRIGHT:
								{
									sibling->right()->color() = BLACK;

									rotation_no_color(sibling->right(), sibling);
									rotation_no_color(parent->left(), parent);

									break;
								}

								case RIGHTLEFT:
								{
									sibling->left()->color() = BLACK;

									rotation_no_color(sibling->left(), sibling);
									rotation_no_color(parent->right(), parent);

									break;
								}

								case RIGHTRIGHT:
								{
									sibling->right()->color() = BLACK;

									rotation_no_color(sibling, parent);

									break;
								}
							}

							find_root();
						}
						else /* Case B: If sibling is BLACK and its both children are BLACK */
						{
							sibling->color() = RED;

							if (parent->color() == BLACK)
							{
								node_base_type *uncle = node_base_type::sibling(parent);
								node_base_type *grand = parent->parent();

								if (grand != NULL)
									fix_delete(grand, uncle);
							}
							else
								parent->color() = BLACK;

							find_root();
						}
					}
					else /* Case C: If sibling is RED */
					{
						node_base_type *grandchild = (sibling == parent->right()) ? sibling->left() : sibling->right();

						rotation_no_color(sibling, parent);
						fix_delete(parent, grandchild);
					}
				}

				node_base_type*
				find_impl(const key_type &k)
				{
					node_base_type *node = m_head;

					while (node)
					{
						const key_type &b = cast(node)->value().first;

						if (do_compare(k, b))
							node = node->left();
						else if (are_keys_equal(k, b))
							return (node);
						else
							node = node->right();
					}

					return (end());
				}

				node_base_type*
				lower_bound_impl(const key_type &k)
				{
					node_base_type *node = begin();
					node_base_type *last = end();

					while (key_comp()(cast(node)->value()->first, k) && node != last)
						node = node_base_type::next(node);

					return (node);
				}

				node_base_type*
				upper_bound_impl(const key_type &k)
				{
					node_base_type *node = lower_bound_impl(k);
					node_base_type *last = end();

					if (node != end() && !(key_comp()(k, cast(node)->value()->first)))
						node = node_base_type::next(node);

					return (node);
				}

			public:
				void
				dump(node_base_type *node, int depth)
				{
					if (node->right())
						dump(node->right(), depth + 1);
//					else
//						printf("%*s NULL\n", (depth + 1) * 4, " ");

					const char *colors[] = { "\e[91m", "\e[96m" };

					printf("%*s%s(%c) %d\033[0m\n", depth * 4, " ", colors[node->color()], "RB"[node->color()], cast(node)->value().first);

					if (node->left())
						dump(node->left(), depth + 1);
//					else
//						printf("%*s NULL\n", (depth + 1) * 4, " ");
				}

				void
				dump()
				{
					if (m_root)
						dump(m_root, 0);
				}
		};
}

#endif /* REDBLACKTREE_HPP_ */
