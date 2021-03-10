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

namespace ft
{
	template<class T, class Container = List<T> >
		class Stack
		{
			public:
				typedef T value_type;
				typedef Container container_type;
				typedef size_t size_type;

			private:
				container_type m_container;

			public:
				explicit
				Stack(const container_type &ctnr = container_type()) :
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
				top(void)
				{
					return (m_container.back());
				}

				const value_type&
				top(void) const
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
