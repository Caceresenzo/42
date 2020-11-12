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

#include <util/Objects.hpp>
#include <iostream>
#include <string>
#include <vector>

# define ENUM_DEFINE(clazz, name, constructor) clazz *clazz::name = clazz::enumValue(#name, constructor);

template<typename E>
	class Enum
	{
		public:
			typedef E *Pointer;
			typedef std::vector<Pointer> Container;
			typedef typename Container::const_iterator iterator;

		private:
			class ContainerWrapper
			{
				private:
					Container m_container;

				public:
					~ContainerWrapper() /* std::vector<*> don't free pointers. */
					{
						iterator ite = m_container.end();

						for (iterator it = m_container.begin(); it != ite; it++)
							delete *it;
					}

					Container&
					storage()
					{
						return (m_container);
					}
			};

		protected:
			std::string m_name;
			int m_ordinal;

		protected:
			Enum() :
					m_name(""),
					m_ordinal(-1)
			{
			}

			static ContainerWrapper&
			enumConstants()
			{
				static ContainerWrapper wrapper; /* Initialization order was causing issues with templates. */

				return (wrapper);
			}

			static int
			nextOrdinal()
			{
				static int ordinal = 0;

				return (ordinal++);
			}

			static const Pointer
			enumValue(const std::string &name, const E &from)
			{
				Pointer value = new E(from);
				value->m_name = name;
				value->m_ordinal = nextOrdinal();

				enumConstants().storage().push_back(value);

				return (value);
			}

		public:
			virtual
			~Enum()
			{
			}

			inline int
			compareTo(const Enum<E> *other) const
			{
				return (compareTo(*Objects::requireNonNull(other)));
			}

			inline int
			compareTo(const Enum<E> &other) const
			{
				return (m_ordinal - other.m_ordinal);
			}

			inline const std::string&
			name() const
			{
				return (m_name);
			}

			inline int
			ordinal() const
			{
				return (m_ordinal);
			}

			inline static const Container&
			values()
			{
				return (enumConstants().storage());
			}
	};

template<typename E>
	std::ostream&
	operator <<(std::ostream &stream, const Enum<E> value)
	{
		return (stream << value.name());
	}

#endif /* ENUM_HPP_ */
