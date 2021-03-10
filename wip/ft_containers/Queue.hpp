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

# include <List.hpp>

namespace ft
{
	template<class T, class Container = List<T> >
		class Queue
		{
			public:
				typedef T value_type;
				typedef Container container_type;
				typedef size_t size_type;

			private:
				container_type m_container;

			public:
				explicit
				Queue(const container_type &ctnr = container_type()) :
						m_container(ctnr)
				{
				}

				bool
				empty(void) const
				{
					return (m_container.empty());
				}

				size_type
				size(void) const
				{
					return (m_container.size());
				}

				value_type&
				front()
				{
					return (m_container.front());
				}

				const value_type&
				front() const
				{
					return (m_container.front());
				}

				value_type&
				back()
				{
					return (m_container.back());
				}

				const value_type&
				back() const
				{
					return (m_container.back());
				}

				void
				push(const value_type &val)
				{
					m_container.push_back(val);
				}

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
