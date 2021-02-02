/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:55:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:55:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONARRAY_HPP_
# define JSONARRAY_HPP_

#include <json/JsonStructure.hpp>
#include <string>
#include <vector>

class JsonArray :
		public JsonStructure
{
	public:
		typedef std::vector<JsonValue*> Container;
		typedef Container::size_type size_type;
		typedef Container::iterator iterator;
		typedef Container::const_iterator const_iterator;

	private:
		Container m_value;

	public:
		JsonArray(void);
		JsonArray(std::vector<JsonValue*> value);
		JsonArray(const JsonArray &other);

		virtual
		~JsonArray(void);

		JsonArray&
		operator =(const JsonArray &other);

		JsonValue&
		operator [](int index);

		const JsonValue&
		operator [](int index) const;

		operator Container(void);
		operator Container(void) const;

		void
		add(JsonValue *value);

		iterator
		begin();

		iterator
		end();

		const_iterator
		begin() const;

		const_iterator
		end() const;

		virtual void
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

#endif /* JSONARRAY_HPP_ */
