/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:07:43 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/21 17:07:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYSEARCHTREE_HPP_
# define BINARYSEARCHTREE_HPP_

# include <cstddef>
# include <iomanip>
# include <iostream>

# include "Algorithm.hpp"
# include "Iterator.hpp"
# include "Utility.hpp"

namespace ft
{
	struct BinarySearchTreeBaseNode
	{
		public:
			typedef BinarySearchTreeBaseNode base_type;
			typedef const BinarySearchTreeBaseNode const_base_type;

		public:
			base_type *parent;
			base_type *left;
			base_type *right;

		public:
			BinarySearchTreeBaseNode() :
					parent(NULL),
					left(NULL),
					right(NULL)
			{
			}

		private:
			static base_type*
			min_impl(base_type *node)
			{
				if (node)
				{
					while (node->left)
						node = node->left;
				}

				return (node);
			}

			static base_type*
			max_impl(base_type *node)
			{
				if (node)
				{
					while (node->right)
						node = node->right;
				}

				return (node);
			}

			static base_type*
			next_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				if (node->right != NULL)
					return (min_impl(node->right));

				return (upUntilLeftChild_impl(node));
			}

			static base_type*
			previous_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				if (node->left != NULL)
					return (max_impl(node->left));

				return (upUntilRightChild_impl(node));
			}

			static base_type*
			upUntilLeftChild_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				while (node->parent != NULL && node != node->parent->left)
					node = node->parent;

				return (node->parent);
			}

			static base_type*
			upUntilRightChild_impl(base_type *node)
			{
				if (!node)
					return (NULL);

				while (node->parent != NULL && node != node->parent->right)
					node = node->parent;

				return (node->parent);
			}

			static size_t
			size_impl(base_type *node)
			{
				if (!node)
					return (0);

				return (size_impl(node->left) + size_impl(node->right) + 1);
			}

		public:
			static base_type*
			min(base_type *node)
			{
				return (min_impl(node));
			}

			static const_base_type*
			min(const_base_type *node)
			{
				return (min_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			max(base_type *node)
			{
				return (max_impl(node));
			}

			static const_base_type*
			max(const_base_type *node)
			{
				return (max_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			next(base_type *node)
			{
				return (next_impl(node));
			}

			static const_base_type*
			next(const_base_type *node)
			{
				return (next_impl(const_cast<base_type*>(node)));
			}

			static base_type*
			previous(base_type *node)
			{
				return (previous_impl(node));
			}

			static const_base_type*
			previous(const_base_type *node)
			{
				return (previous_impl(const_cast<base_type*>(node)));
			}

			static size_t
			size(base_type *node)
			{
				return (size_impl(node));
			}

			static size_t
			size(const_base_type *node)
			{
				return (size_impl(const_cast<base_type*>(node)));
			}
	};

	template<typename T>
		struct BinarySearchTreeNode :
				public BinarySearchTreeBaseNode
		{
			public:
				typedef BinarySearchTreeNode<T> node_type;
				typedef const BinarySearchTreeNode<T> const_node_type;

			public:
				T value;

			public:
				BinarySearchTreeNode(const T &value) :
						value(value)
				{
				}
		};

	template<typename T>
		class BinarySearchTreeIterator;

	template<typename T>
		class BinarySearchTreeConstIterator;

	template<typename T>
		class BinarySearchTreeIterator
		{
			public:
				typedef T value_type;
				typedef T &reference;
				typedef T *pointer;
				typedef bidirectional_iterator_tag iterator_category;
				typedef ptrdiff_t difference_type;

			private:
				typedef BinarySearchTreeIterator<T> iterator_type;
				typedef BinarySearchTreeBaseNode base_node_type;
				typedef BinarySearchTreeNode<T> node_type;

			private:
				base_node_type *m_node;

			public:
				BinarySearchTreeIterator() :
						m_node()
				{
				}

				BinarySearchTreeIterator(base_node_type *node) :
						m_node(node)
				{
				}

				template<typename U>
					BinarySearchTreeIterator(const BinarySearchTreeIterator<U> &other) :
							m_node(other.node())
					{
					}

				~BinarySearchTreeIterator()
				{
				}

				BinarySearchTreeIterator&
				operator=(const BinarySearchTreeIterator &other)
				{
					if (this != &other)
						m_node = other.m_node;

					return (*this);
				}

				iterator_type&
				operator++()
				{
					m_node = BinarySearchTreeBaseNode::next(m_node);

					return (*this);
				}

				iterator_type
				operator++(int)
				{
					iterator_type copy = *this;

					m_node = BinarySearchTreeBaseNode::next(m_node);

					return (copy);
				}

				iterator_type&
				operator--()
				{
					m_node = BinarySearchTreeBaseNode::previous(m_node);

					return (*this);
				}

				iterator_type
				operator--(int)
				{
					iterator_type copy = *this;

					m_node = BinarySearchTreeBaseNode::previous(m_node);

					return (copy);
				}

				reference
				operator*() const
				{
					return (node()->value);
				}

				pointer
				operator->() const
				{
					return (&node()->value);
				}

				base_node_type*
				base_node()
				{
					return (m_node);
				}

				node_type*
				node()
				{
					return (static_cast<node_type*>(m_node));
				}

				base_node_type*
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
					operator==(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const BinarySearchTreeIterator<T> &x, const BinarySearchTreeIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const BinarySearchTreeIterator<T> &x, const BinarySearchTreeIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		class BinarySearchTreeConstIterator
		{
			public:
				typedef T value_type;
				typedef const T &reference;
				typedef const T *pointer;
				typedef bidirectional_iterator_tag iterator_category;
				typedef ptrdiff_t difference_type;

			private:
				typedef BinarySearchTreeIterator<T> iterator_type;
				typedef BinarySearchTreeConstIterator<T> const_iterator_type;

				typedef BinarySearchTreeBaseNode base_node_type;
				typedef BinarySearchTreeNode<T> node_type;
				typedef const BinarySearchTreeBaseNode const_base_node_type;
				typedef const BinarySearchTreeNode<T> const_node_type;

			private:
				const_base_node_type *m_node;

			public:
				BinarySearchTreeConstIterator() :
						m_node()
				{
				}

				BinarySearchTreeConstIterator(const_base_node_type *node) :
						m_node(node)
				{
				}

				BinarySearchTreeConstIterator(const iterator_type &it) :
						m_node(it.base_node())
				{
				}

				template<typename U>
					BinarySearchTreeConstIterator(const BinarySearchTreeIterator<U> &other) :
							m_node(other.base_node())
					{
					}

				template<typename U>
					BinarySearchTreeConstIterator(const BinarySearchTreeConstIterator<U> &other) :
							m_node(other.base_node())
					{
					}

				const_iterator_type&
				operator++()
				{
					m_node = BinarySearchTreeBaseNode::next(m_node);

					return (*this);
				}

				const_iterator_type
				operator++(int)
				{
					const_iterator_type copy = *this;

					m_node = BinarySearchTreeBaseNode::next(m_node);

					return (copy);
				}

				const_iterator_type&
				operator--()
				{
					m_node = BinarySearchTreeBaseNode::previous(m_node);

					return (*this);
				}

				const_iterator_type
				operator--(int)
				{
					const_iterator_type copy = *this;

					m_node = BinarySearchTreeBaseNode::previous(m_node);

					return (copy);
				}

				reference
				operator*() const
				{
					return (node()->value);
				}

				pointer
				operator->() const
				{
					return (&node()->value);
				}

				iterator_type
				remove_const() const
				{
					return (iterator_type(const_cast<base_node_type>(m_node)));
				}

				const_base_node_type*
				base_node()
				{
					return (m_node);
				}

				const_node_type*
				node()
				{
					return (static_cast<const_node_type*>(m_node));
				}

				const_base_node_type*
				base_node() const
				{
					return (m_node);
				}

				const_node_type*
				node() const
				{
					return (static_cast<const_node_type*>(m_node));
				}

				template<typename U>
					friend bool
					operator==(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeConstIterator<U> &x, const BinarySearchTreeIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const BinarySearchTreeIterator<U> &x, const BinarySearchTreeConstIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const BinarySearchTreeConstIterator<T> &x, const BinarySearchTreeConstIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const BinarySearchTreeConstIterator<T> &x, const BinarySearchTreeConstIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		bool
		operator==(const BinarySearchTreeIterator<T> &x, const BinarySearchTreeConstIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const BinarySearchTreeIterator<T> &x, const BinarySearchTreeConstIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		bool
		operator==(const BinarySearchTreeConstIterator<T> &x, const BinarySearchTreeIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const BinarySearchTreeConstIterator<T> &x, const BinarySearchTreeIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<class Key, class T, class Compare, class Alloc>
		class BinarySearchTree
		{
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
				typedef BinarySearchTreeIterator<value_type> iterator;
				typedef BinarySearchTreeConstIterator<value_type> const_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
				typedef size_t size_type;

				typedef BinarySearchTreeBaseNode base_node_type;
				typedef BinarySearchTreeNode<value_type> node_type;
				typedef base_node_type::const_base_type const_base_node_type;
				typedef typename node_type::const_node_type const_node_type;

				typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;

			private:
				Compare m_compare;
				node_allocator_type m_node_allocator;
				base_node_type m_root;
				base_node_type m_last;

			public:
				BinarySearchTree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
						m_compare(comp),
						m_node_allocator(alloc),
						m_root(),
						m_last()
				{
					m_root.right = &m_last;
				}

				~BinarySearchTree()
				{
				}

				BinarySearchTree&
				operator=(const BinarySearchTree &x)
				{
					if (this != &x)
					{
						clear();
						insert(x.begin(), x.end());
					}

					return (*this);
				}

				base_node_type*
				begin()
				{
					return (base_node_type::min(m_root.left) ? : end());
				}

				const_base_node_type*
				begin() const
				{
					return (base_node_type::min(m_root.left) ? : end());
				}

				base_node_type*
				end()
				{
					return (m_root.right);
				}

				const_base_node_type*
				end() const
				{
					return (m_root.right);
				}

				bool
				empty() const
				{
					return (m_root.left == NULL);
				}

				size_type
				size() const
				{
					size_type size = base_node_type::size(m_root.left);

					if (size > 0)
						size--; /* end node */

					return (size);
				}

				size_type
				max_size() const
				{
					return (m_node_allocator.max_size());
				}

				pair<node_type*, bool>
				insert(const_base_node_type *first, const_base_node_type *last)
				{
					while (first != last)
					{
						insert(cast(last)->value);
						first = base_node_type::next(first);
					}
				}

				pair<node_type*, bool>
				insert(const value_type &val)
				{
					return (insert_impl(val));
				}

				void
				erase(base_node_type *node)
				{
					delete_impl(node);
				}

				size_type
				erase(const key_type &k)
				{
					base_node_type *node = find(k);

					if (node != end())
					{
						erase(node);
						return (1);
					}

					return (0);
				}

				void
				erase(base_node_type *first, base_node_type *last)
				{
					while (first != last)
					{
						base_node_type *node = first;
						first = base_node_type::next(node);

						erase(node);
					}
				}

				void
				swap(BinarySearchTree &x)
				{
					if (this != &x)
					{
						unlink_end();
						x.unlink_end();

						ft::swap(m_root.left, x.m_root.left);

						link_end();
						x.link_end();
					}
				}

				void
				clear()
				{
					erase(begin(), end());
				}

				key_compare&
				key_comparator()
				{
					return (m_compare);
				}

				const key_compare&
				key_comparator() const
				{
					return (m_compare);
				}

				base_node_type*
				find(const key_type &k)
				{
					return (find_impl(k));
				}

				const_base_node_type*
				find(const key_type &k) const
				{
					return (remove_const().find_impl(k));
				}

				size_type
				count(const key_type &k) const
				{
					return (find(k) != end() ? 1 : 0);
				}

				base_node_type*
				lower_bound(const key_type &k)
				{
					return (lower_bound_impl(k));
				}

				const_base_node_type*
				lower_bound(const key_type &k) const
				{
					return (remove_const().lower_bound_impl(k));
				}

				base_node_type*
				upper_bound(const key_type &k)
				{
					return (upper_bound_impl(k));
				}

				const_base_node_type*
				upper_bound(const key_type &k) const
				{
					return (remove_const().upper_bound_impl(k));
				}

			private:
				inline BinarySearchTree&
				remove_const() const
				{
					return (const_cast<BinarySearchTree&>(*this));
				}

				inline node_type*
				cast(base_node_type *node)
				{
					return (static_cast<node_type*>(node));
				}

				inline const_node_type*
				cast(const_base_node_type *node) const
				{
					return (const_cast<const_node_type*>(node));
				}

				inline void
				unlink_end()
				{
					if (m_last.parent)
					{
						m_last.parent->right = NULL;
						m_last.parent = NULL;
					}
				}

				inline void
				link_end()
				{
					if (m_root.left)
					{
						m_last.parent = base_node_type::max(m_root.left);

						if (m_last.parent)
							m_last.parent->right = &m_last;
					}
				}

				node_type*
				create_node(base_node_type *parent, const value_type &val)
				{
					node_type *node = m_node_allocator.allocate(1);
					new (node) node_type(val);

					node->parent = parent;

					return (node);
				}

				void
				destroy_node(base_node_type *base)
				{
					node_type *node = cast(base);

					node->~node_type();
					m_node_allocator.deallocate(node, 1);
				}

				pair<node_type*, bool>
				insert_impl(const value_type &val)
				{
					unlink_end();

					pair<node_type*, bool> pr = insert_impl(cast(m_root.left), val);

					link_end();

					return (pr);
				}

				pair<node_type*, bool>
				insert_impl(node_type *node, const value_type &val)
				{
					if (m_root.left == NULL)
					{
						m_root.left = create_node(NULL, val);
						return (ft::make_pair(cast(m_root.left), true));
					}

					if (are_keys_equal(val.first, node->value.first))
						return (ft::make_pair(node, false));

					bool is_left = do_compare(val.first, node->value.first);
					node_type *child = cast(is_left ? node->left : node->right);

					if (child)
						return (insert_impl(child, val));

					child = create_node(node, val);

					if (is_left)
						node->left = child;
					else
						node->right = child;

					return (ft::make_pair(child, true));
				}

				void
				delete_impl(base_node_type *node)
				{
					if (!node || node == end())
						return;

					unlink_end();

					if (m_root.left == node)
						m_root.left = delete_node_impl(node);
					else
					{
						base_node_type *parent = node->parent;
						bool is_left = parent->left == node;
						base_node_type *new_root = delete_node_impl(node);

						if (is_left)
							parent->left = new_root;
						else
							parent->right = new_root;

						if (parent && new_root)
							new_root->parent = parent;
					}

					link_end();
				}

				base_node_type*
				delete_node_impl(base_node_type *root)
				{
					if (root == NULL)
						return (NULL);

					if (root->left && root->right)
					{
						base_node_type *temp = base_node_type::min(root->right);
						cast(root)->value = cast(temp)->value;
						root->right = delete_node_impl(root->right);
					}
					else
					{
						base_node_type *temp = root;

						if (root->left == NULL)
							root = root->right;
						else if (root->right == NULL)
							root = root->left;
						else
							root = NULL;

						destroy_node(temp);
					}

					return (root);
				}

				base_node_type*
				find_impl(const key_type &k)
				{
					base_node_type *node = m_root.left;
					base_node_type *last = end();

					while (node && node != last)
					{
						const key_type &b = cast(node)->value.first;

						if (do_compare(k, b))
							node = node->left;
						else if (are_keys_equal(k, b))
							return (node);
						else
							node = node->right;
					}

					return (last);
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

				base_node_type*
				lower_bound_impl(const key_type &k)
				{
					base_node_type *node = begin();
					base_node_type *last = end();

					while (node != last && do_compare(cast(node)->value.first, k))
						node = base_node_type::next(node);

					return (node);
				}

				base_node_type*
				upper_bound_impl(const key_type &k)
				{
					base_node_type *node = lower_bound_impl(k);
					base_node_type *last = end();

					if (node != last && !do_compare(k, cast(node)->value.first))
						node = base_node_type::next(node);

					return (node);
				}

			public:
				void
				dump(base_node_type *node, int depth)
				{
					if (node->right && node->right != end())
						dump(node->right, depth + 1);

					std::cout << std::setw(depth * 4) << " " << std::setw(0) << cast(node)->value.first << std::endl;

					if (node->left)
						dump(node->left, depth + 1);
				}

				void
				dump()
				{
					if (m_root.left)
						dump(m_root.left, 0);
				}
		};
}

#endif /* BINARYSEARCHTREE_HPP_ */
