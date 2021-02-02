/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enum.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:18:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/10 16:25:05 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_HPP_
# define ENUM_HPP_

#include <exception/Exception.hpp>
#include <util/Object.hpp>
#include <util/Objects.hpp>
#include <iostream>
#include <list>
#include <string>
#include <typeinfo>

# define ENUM_DEFINE(clazz, name, constructor) const clazz *clazz::name = clazz::enumValue(#name, constructor);

template<typename E>
	class Enum :
			public Object
	{
		public:
			typedef std::list<const E*> Container;
			typedef typename Container::iterator iterator;
			typedef typename Container::const_iterator const_iterator;

		private:
			class ContainerWrapper
			{
				private:
					Container m_container;

				public:
					~ContainerWrapper() /* std::vector<*> don't free pointers. */
					{
						for (const_iterator it = m_container.begin(); it != m_container.end(); it++)
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
					Object(),
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

			static const E*
			enumValue(const std::string &name, const E &from)
			{
				E *value = new E(from);
				value->m_name = name;
				value->m_ordinal = nextOrdinal();

				enumConstants().storage().push_back(value);

				return (value);
			}

			virtual std::string
			toString() const
			{
				return (m_name);
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

			inline static Container&
			values()
			{
				return (enumConstants().storage());
			}

			inline static const E*
			find(const std::string &string)
			{
				Container &storage = enumConstants().storage();

				for (iterator it = storage.begin(); it != storage.end(); it++)
					if ((*it)->name() == string)
						return (*it);

				return (NULL);
			}

			inline static const E&
			valueOf(const std::string &string)
			{
				Container &storage = enumConstants().storage();

				for (iterator it = storage.begin(); it != storage.end(); it++)
					if ((*it)->name() == string)
						return (*it);

				throw Exception("Enum value " + std::string(typeid(E).name()) + "." + string + " does not exists");
			}
	};

template<typename E>
	inline bool
	operator ==(const Enum<E> left, const Enum<E> right)
	{
		return (left.ordinal() == right.ordinal());
	}

template<typename E>
	std::ostream&
	operator <<(std::ostream &stream, const Enum<E> value)
	{
		return (stream << value.name());
	}

#endif /* ENUM_HPP_ */
