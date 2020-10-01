/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/30 11:45:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP_
# define LIST_HPP_

# include <memory>
# include "Iterator.hpp"
# include "Algorithm.hpp"

namespace ft
{
	class BaseListNode
	{
		private:
			BaseListNode *_next;
			BaseListNode *_previous;

		public:
			BaseListNode(void)
			{
				this->_next = this;
				this->_previous = this;
			}

			BaseListNode(const BaseListNode &other) :
					_next(other._next),
					_previous(other._previous)
			{
			}

			BaseListNode&
			operator=(const BaseListNode &other)
			{
				if (&other != this)
				{
					this->_next = other._next;
					this->_previous = other._previous;
				}

				return (*this);
			}

			BaseListNode*&
			next()
			{
				return (_next);
			}

			BaseListNode*
			next() const
			{
				return (_next);
			}

			BaseListNode*&
			previous()
			{
				return (_previous);
			}

			BaseListNode*
			previous() const
			{
				return (_previous);
			}

			void
			connect(BaseListNode *to)
			{
				next() = to;
				previous() = to->previous();

				to->previous()->next() = this;
				to->previous() = this;
			}

			BaseListNode*
			disconnect(void)
			{
				BaseListNode *const node = next();

				previous()->next() = node;
				node->previous() = previous();

				return (this);
			}
	};

	template<>
		void
		swap(BaseListNode &x, BaseListNode &y)
		{
			if (x.next() != &x)
			{
				if (y.next() != &y)
				{
					// Both x and y are not empty.
					ft::swap(x.next(), y.next());
					ft::swap(x.previous(), y.previous());
					x.next()->previous() = x.previous()->next() = &x;
					y.next()->previous() = y.previous()->next() = &y;
				}
				else
				{
					// x is not empty, y is empty.
					y.next() = x.next();
					y.previous() = x.previous();
					y.next()->previous() = y.previous()->next() = &y;
					x.next() = x.previous() = &x;
				}
			}
			else if (y.next() != &y)
			{
				// x is empty, y is not empty.
				x.next() = y.next();
				x.previous() = y.previous();
				x.next()->previous() = x.previous()->next() = &x;
				y.next() = y.previous() = &y;
			}
		}

	template<typename T>
		class ListNode :
				public BaseListNode
		{
			private:
				T _data;

			public:
				T&
				data()
				{
					return (_data);
				}

				const T&
				data() const
				{
					return (_data);
				}
		};

	template<class T>
		class ListNormalIterator
		{
			private:
				typedef ListNode<T> Node;

			public:
				typedef ft::bidirectional_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T *pointer;
				typedef T &reference;

			private:
				Node *_node;

			public:
				ListNormalIterator() :
						_node(NULL)
				{
				}

				explicit
				ListNormalIterator(Node *node) :
						_node(node)
				{
				}

				template<typename U>
					ListNormalIterator(const ListNormalIterator<U> &other) :
							_node(other.base())
					{
					}

				~ListNormalIterator()
				{
				}

				ListNormalIterator&
				operator=(const ListNormalIterator &other)
				{
					if (this != &other)
						_node = other._node;

					return (*this);
				}

				ListNormalIterator&
				operator++()
				{
					_node = static_cast<Node*>(_node->next());

					return (*this);
				}

				ListNormalIterator
				operator++(int)
				{
					ListNormalIterator copy = *this;

					_node = static_cast<Node*>(_node->next());

					return (copy);
				}

				ListNormalIterator&
				operator--()
				{
					_node = static_cast<Node*>(_node->previous());

					return (*this);
				}

				ListNormalIterator
				operator--(int)
				{
					ListNormalIterator copy = *this;

					_node = static_cast<Node*>(_node->previous());

					return (copy);
				}

				reference
				operator*() const
				{
					return (static_cast<Node*>(_node)->data());
				}

				pointer
				operator->() const
				{
					return (&static_cast<Node*>(_node)->data());
				}

				Node*
				node() const
				{
					return (_node);
				}
		};

	template<class T>
		class ListConstIterator
		{
			private:
				typedef ListNode<T> Node;

			public:
				typedef ft::bidirectional_iterator_tag iterator_category;
				typedef const T value_type;
				typedef ptrdiff_t difference_type;
				typedef const T *pointer;
				typedef const T &reference;

			private:
				const Node *_node;

			public:
				ListConstIterator() :
						_node(NULL)
				{
				}

				explicit
				ListConstIterator(const Node *ptr) :
						_node(ptr)
				{
				}

				template<typename U>
					ListConstIterator(const ListNormalIterator<U> &other) :
							_node(other.base())
					{
					}

				template<typename U>
					ListConstIterator(const ListConstIterator<U> &other) :
							_node(other.base())
					{
					}

				~ListConstIterator()
				{
				}

				ListConstIterator&
				operator=(const ListConstIterator &other)
				{
					if (this != &other)
						_node = other._node;

					return (*this);
				}

				ListConstIterator&
				operator++()
				{
					_node = static_cast<Node*>(_node->next());

					return (*this);
				}

				ListConstIterator
				operator++(int)
				{
					ListConstIterator copy = *this;

					_node = static_cast<Node*>(_node->next());

					return (copy);
				}

				ListConstIterator&
				operator--()
				{
					_node = static_cast<Node*>(_node->previous());

					return (*this);
				}

				ListConstIterator
				operator--(int)
				{
					ListConstIterator copy = *this;

					_node = static_cast<Node*>(_node->previous());

					return (copy);
				}

				reference
				operator*() const
				{
					return (static_cast<const Node*>(_node)->data());
				}

				pointer
				operator->() const
				{
					return (&static_cast<const Node*>(_node)->data());
				}

				const Node*
				node() const
				{
					return (_node);
				}
		};

	template<typename T>
		inline bool
		operator==(const ListNormalIterator<T> &lhs, const ListNormalIterator<T> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T, typename U>
		inline bool
		operator==(const ListNormalIterator<T> &lhs, const ListNormalIterator<U> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T>
		inline bool
		operator!=(const ListNormalIterator<T> &lhs, const ListNormalIterator<T> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<typename T, typename U>
		inline bool
		operator!=(const ListNormalIterator<T> &lhs, const ListNormalIterator<U> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<typename T>
		inline bool
		operator==(const ListConstIterator<T> &lhs, const ListConstIterator<T> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T, typename U>
		inline bool
		operator==(const ListConstIterator<T> &lhs, const ListConstIterator<U> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T>
		inline bool
		operator!=(const ListConstIterator<T> &lhs, const ListConstIterator<T> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<typename T, typename U>
		inline bool
		operator!=(const ListConstIterator<T> &lhs, const ListConstIterator<U> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<typename T, typename Alloc = std::allocator<T> >
		class List
		{
			public:
				typedef T value_type;
				typedef Alloc allocator_type;
				typedef typename allocator_type::reference reference;
				typedef typename allocator_type::const_reference const_reference;
				typedef typename allocator_type::pointer pointer;
				typedef typename allocator_type::const_pointer const_pointer;
				typedef ListNormalIterator<T> iterator;
				typedef ListConstIterator<T> const_iterator;
				typedef ft::reverse_iterator<iterator> reverse_iterator;
				typedef ft::reverse_iterator<iterator> const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
				typedef size_t size_type;

			private:
				typedef ft::ListNode<T> Node;
				typedef typename Alloc::template rebind<Node>::other NodeAlloc;

			private:
				Node*
				allocate_node(void)
				{
					Node *node = _nodeAllocator.allocate(1);

					node->next() = NULL;
					node->previous() = NULL;

					return (node);
				}

				void
				deallocate_node(Node *node)
				{
					_nodeAllocator.deallocate(node, 1);
				}

				Node*
				create_node(const_reference val)
				{
					Node *node = allocate_node();

					ft::construct_copy(&(node->data()), val);

					return (node);
				}

				Node*
				create_node(void)
				{
					Node *node = allocate_node();

					ft::construct(&(node->data()));

					return (node);
				}

				void
				delete_node(BaseListNode *node)
				{
					delete_node(static_cast<Node*>(node));
				}

				void
				delete_node(Node *node)
				{
					node->disconnect();

					ft::destruct(node->data());
					deallocate_node(node);
				}

			private:
				NodeAlloc _allocator;
				NodeAlloc _nodeAllocator;
				BaseListNode _base;

			public:
				explicit
				List(const allocator_type &alloc = allocator_type()) :
						_allocator(alloc)
				{
				}

				explicit
				List(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
						_allocator(alloc)
				{
					if (n)
						assign(n, val);
				}

				template<class InputIterator>
					List(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :
							_allocator(alloc)
					{
						assign(first, last);
					}

				List(const List &x)
				{
					operator =(x);
				}

				~List()
				{
					clear();
				}

				List&
				operator=(const List &x)
				{
					if (this != &x)
						assign(x.begin(), x.end());

					return (*this);
				}

				iterator
				begin()
				{
					return (iterator(static_cast<Node*>(_base.next())));
				}

				const_iterator
				begin() const
				{
					return (const_iterator(static_cast<Node*>(_base.next())));
				}

				iterator
				end()
				{
					return (iterator(static_cast<Node*>(&_base)));
				}

				const_iterator
				end() const
				{
					return (const_iterator(static_cast<const Node*>(&_base)));
				}

				reverse_iterator
				rbegin()
				{
					return (reverse_iterator(end()));
				}

//				const_reverse_iterator
//				rbegin() const
//				{
//					return (const_reverse_iterator(reverse_iterator(end())));
//				}

				reverse_iterator
				rend()
				{
					return (reverse_iterator(begin()));
				}

//				const_reverse_iterator
//				rend() const
//				{
//					return (const_reverse_iterator(reverse_iterator(begin())));
//				}

				bool
				empty() const
				{
					return (_base.next() == &_base);
				}

				size_type
				size() const
				{
					size_type length = 0;
					BaseListNode *node = _base.next();

					while (node != &_base)
					{
						length++;
						node = node->next();
					}

					return (length);
				}

				reference
				front()
				{
					return (*begin());
				}

				const_reference
				front() const
				{
					return (*begin());
				}

				reference
				back()
				{
					return (*(--end()));
				}

				const_reference
				back() const
				{
					return (*(--end()));
				}

				template<class InputIterator>
					void
					assign(InputIterator first, InputIterator last)
					{
						List l;

						while (first != last)
							l.push_back(*first++);

						swap(l);
					}

				void
				assign(size_type n, const value_type &val)
				{
					List l;

					while (n--)
						l.push_back(val);

					swap(l);
				}

				void
				push_front(const value_type &val)
				{
					create_node(val)->connect(_base.next());
				}

				void
				pop_front(void)
				{
					erase(begin());
				}

				void
				push_back(const value_type &val)
				{
					create_node(val)->connect(_base.previous()->next());
				}

				void
				pop_back(void)
				{
					erase(--end());
				}

				iterator
				insert(iterator position, const value_type &val)
				{
					insert(position, 1, val);

					return (iterator(position.node()->next()));
				}

				void
				insert(iterator position, size_type n, const value_type &val)
				{
					if (n)
					{
						List l;

						iterator it = begin();

						while (it != position)
							l.push_back(*it++);

						while (n--)
							l.push_back(val);

						iterator ite = end();
						while (it != ite)
							l.push_back(*it++);

						swap(l);
					}
				}

				template<class InputIterator>
					void
					insert(iterator position, InputIterator first, InputIterator last)
					{
						if (first != last)
						{
							List l;

							iterator it = begin();

							while (it != position)
								l.push_back(*it++);

							while (first != last)
								l.push_back(*first++);

							iterator ite = end();
							while (it != ite)
								l.push_back(*it++);

							swap(l);
						}
					}

				iterator
				erase(iterator position)
				{
					Node *node = position.node();
					Node *next = static_cast<Node*>(node->next());

					delete_node(node);

					return (iterator(next));
				}

				iterator
				erase(iterator first, iterator last)
				{
					iterator it = iterator(first);

					while (it != last)
					{
						Node *node = it.node();
						it++;

						delete_node(node);
					}

					return (iterator(last));
				}

				void
				swap(List &x)
				{
					ft::swap(_base, x._base);
				}

				void
				resize(size_type n, value_type val = value_type())
				{
					size_type len = size();

					if (n < len)
						erase(ft::next(begin(), n), end());
					else if (n > size())
						insert(end(), n - len, val);
				}

				void
				clear()
				{
					erase(begin(), end());
				}
		};

	template<class T, class Alloc>
		bool
		operator==(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template<class T, class Alloc>
		bool
		operator!=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

	template<class T, class Alloc>
		bool
		operator<(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template<class T, class Alloc>
		bool
		operator<=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (!(rhs < lhs));
		}

	template<class T, class Alloc>
		bool
		operator>(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (rhs < lhs);
		}

	template<class T, class Alloc>
		bool
		operator>=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
		{
			return (!(lhs < rhs));
		}

	template<class T, class Alloc>
		void
		swap(List<T, Alloc> &x, List<T, Alloc> &y)
		{
			x.swap(y);
		}
}

#endif /* LIST_HPP_ */
