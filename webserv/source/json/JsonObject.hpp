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

#include <json/JsonStructure.hpp>
#include <map>
#include <string>

class JsonObject :
		public JsonStructure
{
	public:
		typedef std::map<std::string, JsonValue*> Container;
		typedef Container::size_type size_type;
		typedef Container::iterator iterator;
		typedef Container::const_iterator const_iterator;

	private:
		Container m_value;

	public:
		JsonObject(void);
		JsonObject(Container value);
		JsonObject(const JsonObject &other);

		virtual
		~JsonObject(void);

		JsonObject&
		operator =(const JsonObject &other);

		operator Container(void);

		operator Container(void) const;

		void
		put(const std::string &name, JsonValue *value);

		bool
		has(const std::string &name) const;

		JsonValue*
		get(const std::string &name);

		const JsonValue*
		get(const std::string &name) const;

		iterator
		begin();

		iterator
		end();

		const_iterator
		begin() const;

		const_iterator
		end() const;

		iterator
		find(const std::string &key);

		const_iterator
		find(const std::string &key) const;

		void
		clear(void);

		bool
		empty() const;

		Container::size_type
		size() const;

		JsonValue*
		clone(void) const;

		Type
		type(void) const;

		const std::string
		toJsonString(void) const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONOBJECT_HPP_ */
