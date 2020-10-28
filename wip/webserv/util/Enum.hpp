/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enum.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:18:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 15:18:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_HPP_
# define ENUM_HPP_

# include <iostream>
# include <vector>

# define ENUM_DEFINE(clazz, name, constructor) clazz *clazz::name = clazz::enumValue(#name, constructor);

template<typename E>
	class Enum
	{
		public:
			typedef E *Pointer;
			typedef std::vector<Pointer> Container;
			typedef typename Container::const_iterator iterator;

		private:
			static int s_ordinal;
			static Container m_values;

		protected:
			std::string m_name;
			int m_ordinal;

		protected:
			Enum() :
					m_name(""),
					m_ordinal(-1)
			{
			}

			static const Pointer
			enumValue(const std::string &name, const E &from)
			{
				Pointer value = new E(from);
				value->m_name = name;
				value->m_ordinal = s_ordinal++;

				m_values.push_back(value);

				return (value);
			}

		public:
			virtual
			~Enum()
			{
			}

			const std::string&
			name() const
			{
				return (m_name);
			}

			int
			ordinal() const
			{
				return (m_ordinal);
			}

			static const Container&
			values()
			{
				return (m_values);
			}
	};

template<typename E>
	int Enum<E>::s_ordinal = 0;

template<typename E>
	typename Enum<E>::Container Enum<E>::m_values;

template<typename E>
	std::ostream&
	operator <<(std::ostream &stream, const Enum<E> value)
	{
		return (stream << value.name());
	}

#endif /* ENUM_HPP_ */
