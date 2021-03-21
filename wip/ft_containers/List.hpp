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

#include <Algorithm.hpp>
#include <Functional.hpp>
#include <Iterator.hpp>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <assert.h>

namespace ft
{
	struct ListBaseNode
	{
		public:
			typedef ListBaseNode base_type;
			typedef const ListBaseNode const_base_type;

		public:
			ListBaseNode *next;
			ListBaseNode *previous;

		public:
			ListBaseNode(void) :
					next(this),
					previous(this)
			{
			}

			void
			connect(base_type *to)
			{
				next = to;
				previous = to->previous;

				to->previous->next = this;
				to->previous = this;
			}

			void
			connect_next(base_type *to)
			{
				to->next = next;
				to->previous = this;

				next->previous = to;
				next = to;
			}

			base_type*
			disconnect(void)
			{
				base_type *node = next;

				previous->next = node;
				node->previous = previous;

				return (this);
			}

			void
			transfer(base_type *first, base_type *last) _GLIBCXX_USE_NOEXCEPT
			{
				// from: https://gcc.gnu.org/git/?p=gcc.git;a=blob_plain;f=libstdc%2B%2B-v3/src/c%2B%2B98/list.cc;hb=6bbf0dec66c0e719b06cd2fe67559fda6df09000
				if (this != last)
				{
					/* Remove [first, last) from its old position. */
					last->previous->next = this;
					first->previous->next = last;
					this->previous->next = first;

					/* Splice [first, last) into its new position. */
					base_type *tmp = this->previous;
					this->previous = last->previous;
					last->previous = first->previous;
					first->previous = tmp;
				}
			}

			void
			reverse()
			{
				ListBaseNode *node = this;

				do
				{
					ft::swap(node->next, node->previous);

					node = node->previous; /* was `next` before the swap */
				}
				while (node != this);
			}

			static void
			swap(base_type &x, base_type &y)
			{
				if (x.next != &x)
				{
					if (y.next != &y) /* Both __x and __y are not empty. */
					{
						ft::swap(x.next, y.next);
						ft::swap(x.previous, y.previous);
						x.next->previous = x.previous->next = &x;
						y.next->previous = y.previous->next = &y;
					}
					else /* x is not empty, y is empty. */
					{
						y.next = x.next;
						y.previous = x.previous;
						y.next->previous = y.previous->next = &y;
						x.next = x.previous = &x;
					}
				}
				else if (y.next != &y) /* x is empty, y is not empty. */
				{
					x.next = y.next;
					x.previous = y.previous;
					x.next->previous = x.previous->next = &x;
					y.next = y.previous = &y;
				}
			}
	};

	template<typename T>
		struct ListNode :
				public ListBaseNode
		{
			public:
				typedef ListNode<T> node_type;
				typedef const ListNode<T> const_node_type;

			public:
				T value;

			public:
				ListNode(const T &value) :
						value(value)
				{
				}
		};

	template<class T>
		class ListIterator;

	template<class T>
		class ListConstIterator;

	template<class T>
		class ListIterator
		{
			public:
				typedef ft::bidirectional_iterator_tag iterator_category;
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T *pointer;
				typedef T &reference;

			private:
				typedef ListIterator<T> iterator_type;
				typedef ListBaseNode base_node_type;
				typedef ListNode<T> node_type;

			private:
				base_node_type *m_node;

			public:
				ListIterator() :
						m_node(NULL)
				{
				}

				explicit
				ListIterator(base_node_type *node) :
						m_node(node)
				{
				}

				template<typename U>
					ListIterator(const ListIterator<U> &other) :
							m_node(other.base_node())
					{
					}

				iterator_type&
				operator++()
				{
					m_node = m_node->next;

					return (*this);
				}

				iterator_type
				operator++(int)
				{
					iterator_type copy = *this;

					m_node = m_node->next;

					return (copy);
				}

				iterator_type&
				operator--()
				{
					m_node = m_node->previous;

					return (*this);
				}

				iterator_type
				operator--(int)
				{
					iterator_type copy = *this;

					m_node = m_node->previous;

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
					operator==(const ListIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const ListConstIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListConstIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const ListIterator<U> &x, const ListConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListIterator<U> &x, const ListConstIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const ListIterator<T> &x, const ListIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const ListIterator<T> &x, const ListIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<class T>
		class ListConstIterator
		{
			public:
				typedef ft::bidirectional_iterator_tag iterator_category;
				typedef const T value_type;
				typedef ptrdiff_t difference_type;
				typedef const T *pointer;
				typedef const T &reference;

			private:
				typedef ListIterator<T> iterator_type;
				typedef ListConstIterator<T> const_iterator_type;
				typedef ListBaseNode base_node_type;
				typedef ListNode<T> node_type;
				typedef const ListBaseNode const_base_node_type;
				typedef const ListNode<T> const_node_type;

			private:
				const_base_node_type *m_node;

			public:
				ListConstIterator() :
						m_node(NULL)
				{
				}

				explicit
				ListConstIterator(const_base_node_type *node) :
						m_node(node)
				{
				}

				ListConstIterator(const iterator_type &it) :
						m_node(it.base_node())
				{
				}

				template<typename U>
					ListConstIterator(const ListIterator<U> &other) :
							m_node(other.base_node())
					{
					}

				template<typename U>
					ListConstIterator(const ListConstIterator<U> &other) :
							m_node(other.base_node())
					{
					}

				const_iterator_type&
				operator++()
				{
					m_node = m_node->next;

					return (*this);
				}

				const_iterator_type
				operator++(int)
				{
					const_iterator_type copy = *this;

					m_node = m_node->next;

					return (copy);
				}

				const_iterator_type&
				operator--()
				{
					m_node = m_node->previous;

					return (*this);
				}

				const_iterator_type
				operator--(int)
				{
					const_iterator_type copy = *this;

					m_node = m_node->previous;

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
					operator==(const ListConstIterator<U> &x, const ListConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListConstIterator<U> &x, const ListConstIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const ListConstIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListConstIterator<U> &x, const ListIterator<U> &y);

				template<typename U>
					friend bool
					operator==(const ListIterator<U> &x, const ListConstIterator<U> &y);

				template<typename U>
					friend bool
					operator!=(const ListIterator<U> &x, const ListConstIterator<U> &y);
		};

	template<typename T>
		bool
		operator==(const ListConstIterator<T> &x, const ListConstIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const ListConstIterator<T> &x, const ListConstIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		bool
		operator==(const ListIterator<T> &x, const ListConstIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const ListIterator<T> &x, const ListConstIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T>
		bool
		operator==(const ListConstIterator<T> &x, const ListIterator<T> &y)
		{
			return (x.m_node == y.m_node);
		}

	template<typename T>
		bool
		operator!=(const ListConstIterator<T> &x, const ListIterator<T> &y)
		{
			return (x.m_node != y.m_node);
		}

	template<typename T, typename U>
		inline bool
		operator==(const ListConstIterator<T> &lhs, const ListConstIterator<U> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T, typename U>
		inline bool
		operator!=(const ListConstIterator<T> &lhs, const ListConstIterator<U> &rhs)
		{
			return (!(lhs.node() == rhs.node()));
		}

	template<typename T, typename U>
		inline bool
		operator==(const ListConstIterator<T> &lhs, const ListIterator<U> &rhs)
		{
			return (lhs.node() == rhs.node());
		}

	template<typename T, typename U>
		inline bool
		operator!=(const ListConstIterator<T> &lhs, const ListIterator<U> &rhs)
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
				typedef ListIterator<T> iterator;
				typedef ListConstIterator<T> const_iterator;
				typedef ft::reverse_iterator<iterator> reverse_iterator;
				typedef ft::reverse_iterator<iterator> const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
				typedef size_t size_type;

			private:
				typedef ListBaseNode base_node_type;
				typedef ListNode<value_type> node_type;
				typedef base_node_type::const_base_type const_base_node_type;
				typedef typename node_type::const_node_type const_node_type;

				typedef typename Alloc::template rebind<node_type>::other node_allocator_type;

			private:
				node_allocator_type m_allocator;
				node_allocator_type m_node_allocator;
				ListBaseNode m_base;

			public:
				explicit
				List(const allocator_type &alloc = allocator_type()) :
						m_allocator(alloc)
				{
				}

				explicit
				List(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
						m_allocator(alloc)
				{
					if (n)
						assign(n, val);
				}

				template<class InputIterator>
					List(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :
							m_allocator(alloc)
					{
						assign(first, last);
					}

				List(const List &x)
				{
					assign(x.begin(), x.end());
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

				/**
				 * Returns an iterator pointing to the first element in the list container.
				 * Notice that, unlike member ::front, which returns a reference to the first element, this function returns a bidirectional iterator pointing to it.
				 * If the container is empty, the returned iterator value shall not be dereferenced.
				 *
				 * @return An iterator to the beginning of the sequence container.
				 */
				iterator
				begin()
				{
					return (iterator(m_base.next));
				}

				/**
				 * Returns an iterator pointing to the first element in the list container.
				 * Notice that, unlike member ::front, which returns a reference to the first element, this function returns a bidirectional iterator pointing to it.
				 * If the container is empty, the returned iterator value shall not be dereferenced.
				 *
				 * @return A const-qualified iterator to the beginning of the sequence container.
				 */
				const_iterator
				begin() const
				{
					return (const_iterator(m_base.next));
				}

				/**
				 * Returns an iterator referring to the past-the-end element in the list container.
				 * The past-the-end element is the theoretical element that would follow the last element in the list container. It does not point to any element, and thus shall not be dereferenced.
				 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with ::begin to specify a range including all the elements in the container.
				 * If the container is empty, this function returns the same as ::begin.
				 *
				 * An iterator to the element past the end of the sequence.
				 */
				iterator
				end()
				{
					return (iterator(&m_base));
				}

				/**
				 * Returns an iterator referring to the past-the-end element in the list container.
				 * The past-the-end element is the theoretical element that would follow the last element in the list container. It does not point to any element, and thus shall not be dereferenced.
				 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with ::begin to specify a range including all the elements in the container.
				 * If the container is empty, this function returns the same as ::begin.
				 *
				 * A const-qualified iterator to the element past the end of the sequence.
				 */
				const_iterator
				end() const
				{
					return (const_iterator(&m_base));
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
					return (const_reverse_iterator(end()));
				}

				/**
				 * Returns whether the list container is empty (i.e. whether its size is 0).
				 * This function does not modify the container in any way. To clear the content of a list container, see ::clear.
				 *
				 * @return true if the container size is 0, false otherwise.
				 */
				bool
				empty() const
				{
					return (m_base.next == &m_base);
				}

				/**
				 * Returns the number of elements in the list container.
				 *
				 * @return The number of elements in the container.
				 */
				size_type
				size() const
				{
					return (ft::distance(begin(), end()));
				}

				/**
				 * Returns the maximum number of elements that the list container can hold.
				 * This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
				 *
				 * @return The maximum number of elements the object can hold as content.
				 */
				size_type
				max_size() const
				{
					return (m_allocator.max_size());
				}

				/**
				 * Returns a reference to the first element in the list container.
				 * Unlike member list::begin, which returns an iterator to this same element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the first element in the list container.
				 */
				reference
				front()
				{
					return (*begin());
				}

				/**
				 * Returns a reference to the first element in the list container.
				 * Unlike member list::begin, which returns an iterator to this same element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A const-qualified reference to the first element in the list container.
				 */
				const_reference
				front() const
				{
					return (*begin());
				}

				/**
				 * Returns a reference to the last element in the list container.
				 * Unlike member list::end, which returns an iterator just past this element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A reference to the last element in the list.
				 */
				reference
				back()
				{
					return (*(--end()));
				}

				/**
				 * Returns a reference to the last element in the list container.
				 * Unlike member list::end, which returns an iterator just past this element, this function returns a direct reference.
				 * Calling this function on an empty container causes undefined behavior.
				 *
				 * @return A  const-qualified reference to the last element in the list.
				 */
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
					create_node(val)->connect(m_base.next);
				}

				void
				pop_front(void)
				{
					erase(begin());
				}

				void
				push_back(const value_type &val)
				{
					create_node(val)->connect(&m_base);
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

					return (iterator(position.node()->next));
				}

				void
				insert(iterator position, size_type n, const value_type &val)
				{
					List lst(n, val, m_allocator);

					splice(position, lst);
				}

				template<class InputIterator>
					void
					insert(iterator position, InputIterator first, InputIterator last)
					{
						List lst(first, last, m_allocator);
						splice(position, lst);
					}

				iterator
				erase(iterator position)
				{
					base_node_type *node = position.base_node();
					base_node_type *next = node->next;

					destroy_node(node);

					return (iterator(next));
				}

				iterator
				erase(iterator first, iterator last)
				{
					iterator it = iterator(first);

					while (it != last)
					{
						base_node_type *node = it.base_node();
						it++;

						destroy_node(node);
					}

					return (iterator(last));
				}

				void
				swap(List &x)
				{
					ListBaseNode::swap(m_base, x.m_base);
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

				void
				splice(iterator position, List &x)
				{
					if (!x.empty())
						position.node()->transfer(x.begin().node(), x.end().node());
				}

				void
				splice(iterator position, List &x, iterator i)
				{
					iterator next = i;
					++next;

					if (i != next) /* check of emptiness at the same time */
						position.node()->transfer(i.node(), ft::next(i).node());

					(void)x;
				}

				void
				splice(iterator position, List &x, iterator first, iterator last)
				{
					if (first != last) /* check of emptiness at the same time */
						position.node()->transfer(first.node(), last.node());

					(void)x;
				}

				void
				remove(const value_type &val)
				{
					iterator it = this->begin();
					iterator end = this->end();
					iterator input = end;

					if (it == end)
						return; /* empty */

					while (it != end)
					{
						if (*it == val)
						{
							if (&val == &*it)
								input = it++; /* avoid deleting if item is one the list */
							else
								it = erase(it);
						}
						else
							it++;
					}

					if (input != end)
						erase(input);
				}

				template<class Predicate>
					void
					remove_if(Predicate pred)
					{
						iterator it = this->begin();
						iterator end = this->end();

						if (it == end)
							return; /* empty */

						while (it != end)
						{
							if (pred(*it))
								it = erase(it);
							else
								it++;
						}
					}

				void
				unique()
				{
					unique(ft::equal_to<value_type>());
				}

				template<class BinaryPredicate>
					void
					unique(BinaryPredicate binary_pred)
					{
						iterator it = this->begin();
						iterator end = this->end();

						if (it == end || ++it == end)
							return; /* empty, or single element */

						while (it != end)
						{
							iterator previous = it;
							--previous;

							if (binary_pred(*it, *previous))
								it = erase(it);
							else
								it++;
						}
					}

				void
				sort()
				{
					sort(ft::less<value_type>());
				}

				node_type*
				cast(base_node_type *base)
				{
					return (static_cast<node_type*>(base));
				}

				template<class Compare>
					void
					sort(Compare comp)
					{
						bool swapped;
						base_node_type *current;
						base_node_type *last = &m_base;

						do
						{
							swapped = 0;
							current = begin().node();

							while (current->next != last)
							{
								if (comp(cast(current->next)->value, cast(current)->value))
								{
									ListBaseNode &x = *current;
									ListBaseNode &y = *current->next;

									x.next = y.next;
									y.previous = x.previous;
									x.next->previous = &x;
									y.previous->next = &y;
									y.next = &x;
									x.previous = &y;

									swapped = true;
								}
								else
									current = current->next;
							}

							last = current;
						}
						while (swapped);
					}

				void
				merge(List &x)
				{
					merge(x, std::less<value_type>());
				}

				template<class Compare>
					void
					merge(List &x, Compare comp)
					{
						if (this == &x || x.empty())
							return;

						iterator first1 = begin();
						iterator last1 = end();
						iterator first2 = x.begin();
						iterator last2 = x.end();

						while (first1 != last1 && first2 != last2)
						{
							if (comp(*first2, *first1))
							{
								iterator next = first2;
								first1.node()->transfer(first2.node(), (++next).node());
								first2 = next;
							}
							else
								++first1;
						}

						if (first2 != last2)
							last1.node()->transfer(first2.node(), last2.node());
					}

				void
				reverse()
				{
					m_base.reverse();
				}

			private:
				node_type*
				create_node(const_reference val)
				{
					node_type *node = m_node_allocator.allocate(1);
					new (node) node_type(val);

					return (node);
				}

				void
				destroy_node(base_node_type *base)
				{
					node_type *node = cast(base);

					node->disconnect();
					node->~node_type();

					m_node_allocator.deallocate(node, 1);
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
