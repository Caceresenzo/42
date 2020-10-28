/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContainerBuilder.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:47:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 16:47:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERBUILDER_HPP_
# define CONTAINERBUILDER_HPP_

#include <vector>

template<typename T, typename Container = std::vector<T> >
	class ContainerBuilder
	{
		private:
			Container m_container;

		public:
			ContainerBuilder(void) :
					m_container()
			{
			}

			ContainerBuilder(const Container &initial) :
					m_container(initial)
			{
			}

			ContainerBuilder(const ContainerBuilder &other) :
					m_container(other.m_container)
			{
			}

			virtual
			~ContainerBuilder()
			{
			}

			ContainerBuilder&
			add(const T &t)
			{
				m_container.push_back(t);

				return (*this);
			}

			Container
			build(void) const
			{
				return (m_container);
			}
	};

#endif /* CONTAINERBUILDER_HPP_ */
