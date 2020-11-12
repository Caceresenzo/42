/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:31:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONOBJECT_HPP_
# define JSONOBJECT_HPP_

#include <util/json/JsonStructure.hpp>
#include <util/json/JsonValue.hpp>
#include <map>
#include <string>
#include <utility>

class JsonObject :
		public JsonStructure
{
	public:
		typedef std::map<std::string, JsonValue*> Container;
		typedef typename Container::size_type size_type;
		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;

	private:
		Container m_value;

	public:
		JsonObject(void) :
				m_value()
		{
		}

		JsonObject(Container value) :
				m_value(value)
		{
		}

		JsonObject(const JsonObject &other) :
				m_value()
		{
			operator =(other);
		}

		virtual
		~JsonObject(void)
		{
			clear();
		}

		JsonObject&
		operator =(const JsonObject &other)
		{
			if (this != &other)
			{
				const_iterator it = other.m_value.begin();
				const_iterator ite = other.m_value.end();

				clear();

				for (; it != ite; it++)
					m_value.insert(m_value.end(), std::make_pair(it->first, it->second->clone()));
			}

			return (*this);
		}

		operator Container(void)
		{
			return (m_value);
		}

		operator Container(void) const
		{
			return (m_value);
		}

		void
		put(const std::string &name, JsonValue *value)
		{
			m_value.insert(m_value.end(), std::make_pair(name, value));
		}

		bool
		has(const std::string &name) const
		{
			return (m_value.find(name) != m_value.end());
		}

		JsonValue*
		get(const std::string &name)
		{
			const_iterator it = m_value.find(name);

			if (it == m_value.end())
				return (NULL);

			return (it->second);
		}

		inline iterator
		begin()
		{
			return (m_value.begin());
		}

		inline iterator
		end()
		{
			return (m_value.end());
		}

		inline const_iterator
		begin() const
		{
			return (m_value.begin());
		}

		inline const_iterator
		end() const
		{
			return (m_value.end());
		}

		virtual void
		clear(void)
		{
			if (m_value.empty())
				return;

			iterator it = m_value.begin();
			iterator ite = m_value.end();

			for (; it != ite; it++)
				delete it->second;

			return (m_value.clear());
		}

		JsonValue*
		clone(void) const
		{
			return (new JsonObject(*this));
		}

		const Type
		type(void) const
		{
			return (TYPE_ARRAY);
		}

		const std::string
		toJsonString(void) const;
};

#endif /* JSONOBJECT_HPP_ */
