/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:56:21 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 13:56:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP_
# define STACK_HPP_

# include <List.hpp>
# include <stddef.h>

namespace ft
{
	/**
	 * Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container.
	 * stacks are implemented as container adaptors, which are classes that use an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
	 * The underlying container may be any of the standard container class templates or some other specifically designed container class. The container shall support the following operations:
	 * - empty
	 * - size
	 * - back
	 * - push_back
	 * - pop_back
	 * The standard container classes vector, deque and list fulfill these requirements. By default, if no container class is specified for a particular stack class instantiation, the standard container deque is used.
	 *
	 * @tparam T Type of the elements.
	 * @tparam Container Type of the internal underlying container object where the elements are stored.
	 */
	template<class T, class Container = List<T> >
		class Stack
		{
			public:
				/** The first template parameter (T) */
				typedef T value_type;

				/** The second template parameter (Container) */
				typedef Container container_type;

				/** An unsigned integral type */
				typedef size_t size_type;

			private:
				container_type m_container;

			public:
				/**
				 * Constructs a stack container adaptor object.
				 *
				 * @param ctnr Container object.
				 */
				explicit
				Stack(const container_type &ctnr = container_type()) :
						m_container(ctnr)
				{
				}

				/**
				 * Returns whether the stack is empty: i.e. whether its size is zero.
				 * This member function effectively calls member empty of the underlying container object.
				 *
				 * @return true if the underlying container's size is 0, false otherwise.
				 */
				bool
				empty(void) const
				{
					return (m_container.empty());
				}

				/**
				 * Returns the number of elements in the stack.
				 * This member function effectively calls member size of the underlying container object.
				 *
				 * @return The number of elements in the underlying container.
				 */
				size_type
				size(void) const
				{
					return (m_container.size());
				}

				/**
				 * Returns a reference to the top element in the stack.
				 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
				 * This member function effectively calls member back of the underlying container object.
				 *
				 * @return A reference to the top element in the stack.
				 */
				value_type&
				top(void)
				{
					return (m_container.back());
				}

				/**
				 * Returns a reference to the top element in the stack.
				 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
				 * This member function effectively calls member back of the underlying container object.
				 *
				 * @return A const-qualified reference to the top element in the stack.
				 */
				const value_type&
				top(void) const
				{
					return (m_container.back());
				}

				/**
				 * Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
				 * This member function effectively calls the member function push_back of the underlying container object.
				 *
				 * @param val Value to which the inserted element is initialized.
				 */
				void
				push(const value_type &val)
				{
					m_container.push_back(val);
				}

				/**
				 * Removes the element on top of the stack, effectively reducing its size by one.
				 * The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member ::top.
				 * This calls the removed element's destructor.
				 * This member function effectively calls the member function pop_back of the underlying container object.s
				 */
				void
				pop(void)
				{
					m_container.pop_back();
				}

				template<class T_, class Container_>
					friend bool
					operator==(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator!=(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<=(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>=(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);
		};

	template<class T, class Container>
		bool
		operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container == rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container != rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container < rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container <= rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container > rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
		{
			return (lhs.m_container >= rhs.m_container);
		}
}

#endif /* STACK_HPP_ */
