/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:07:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 15:07:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP_
# define QUEUE_HPP_

# include <stddef.h>

# include "List.hpp"

namespace ft
{
	/**
	 * Queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out), where elements are inserted into one end of the container and extracted from the other.
	 * Queues are implemented as containers adaptors, which are classes that use an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. Elements are pushed into the "back" of the specific container and popped from its "front".
	 * The underlying container may be one of the standard container class template or some other specifically designed container class. This underlying container shall support at least the following operations:
	 * - empty
	 * - size
	 * - front
	 * - back
	 * - push_back
	 * - pop_front
	 * The standard container classes deque and list fulfill these requirements. By default, if no container class is specified for a particular queue class instantiation, the standard container deque is used.
	 *
	 * @tparam T Type of the elements.
	 * @tparam Container Type of the internal underlying container object where the elements are stored.
	 */
	template<class T, class Container = List<T> >
		class Queue
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
				 * Constructs a queue container adaptor object.
				 *
				 * @param ctnr Container object.
				 */
				explicit
				Queue(const container_type &ctnr = container_type()) :
						m_container(ctnr)
				{
				}

				/**
				 * Returns whether the queue is empty: i.e. whether its size is zero.
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
				 * Returns the number of elements in the queue.
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
				 * Returns a reference to the next element in the queue.
				 * The next element is the "oldest" element in the queue and the same element that is popped out from the queue when ::pop is called.
				 * This member function effectively calls member front of the underlying container object.
				 *
				 * @return A reference to the next element in the queue.
				 */
				value_type&
				front()
				{
					return (m_container.front());
				}

				/**
				 * Returns a reference to the next element in the queue.
				 * The next element is the "oldest" element in the queue and the same element that is popped out from the queue when ::pop is called.
				 * This member function effectively calls member front of the underlying container object.
				 *
				 * @return A const-qualified reference to the next element in the queue.
				 */
				const value_type&
				front() const
				{
					return (m_container.front());
				}

				/**
				 * Returns a reference to the last element in the queue. This is the "newest" element in the queue (i.e. the last element pushed into the queue).
				 * This member function effectively calls member back of the underlying container object.
				 *
				 * @return A reference to the last element in the queue.
				 */
				value_type&
				back()
				{
					return (m_container.back());
				}

				/**
				 * Returns a reference to the last element in the queue. This is the "newest" element in the queue (i.e. the last element pushed into the queue).
				 * This member function effectively calls member back of the underlying container object.
				 *
				 * @return A const-qualified reference to the last element in the queue.
				 */
				const value_type&
				back() const
				{
					return (m_container.back());
				}

				/**
				 * Inserts a new element at the end of the queue, after its current last element. The content of this new element is initialized to val.
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
				 * Removes the next element in the queue, effectively reducing its size by one.
				 * The element removed is the "oldest" element in the queue whose value can be retrieved by calling member ::front.
				 * This calls the removed element's destructor.
				 * This member function effectively calls the member function pop_front of the underlying container object.
				 */
				void
				pop(void)
				{
					m_container.pop_front();
				}

				template<class T_, class Container_>
					friend bool
					operator==(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator!=(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<=(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>=(const Queue<T_, Container_> &lhs, const Queue<T_, Container_> &rhs);
		};

	template<class T, class Container>
		bool
		operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container == rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container != rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container < rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container <= rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container > rhs.m_container);
		}

	template<class T, class Container>
		bool
		operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
		{
			return (lhs.m_container >= rhs.m_container);
		}
}

#endif /* QUEUE_HPP_ */
