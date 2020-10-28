/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:18:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:18:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONOBJECT_HPP_
# define JSONOBJECT_HPP_

# include <util/json/JSONBase.hpp>
# include <util/json/JSONType.hpp>
# include <string>
# include <map>

class JSONObject :
		public JSONBase
{
	public:
		typedef std::map<std::string, JSONType> container;
		typedef container::size_type size_type;
		typedef container::iterator iterator;
		typedef container::const_iterator const_iterator;

	private:
		container m_map;

	public:
		JSONObject(void);
		JSONObject(container map);
		JSONObject(const JSONObject &other);

		virtual
		~JSONObject();

		JSONObject&
		operator =(const JSONObject &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		size_type
		size(void);

		void
		put(const std::string &key, JSONType value);

		bool
		has(const std::string &key) const;

		JSONType&
		get(const std::string &key);

		iterator
		find(const std::string &key);

		const_iterator
		find(const std::string &key) const;

		iterator
		begin(void);

		const_iterator
		begin(void) const;

		iterator
		end(void);

		const_iterator
		end(void) const;

		container&
		value(void);
};

#endif /* JSONOBJECT_HPP_ */
