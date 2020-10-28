/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONArray.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:08:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:08:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONARRAY_HPP_
# define JSONARRAY_HPP_

# include <util/json/JSONBase.hpp>
# include <util/json/JSONType.hpp>
# include <vector>

// TODO Deep copy
class JSONArray :
		public JSONBase
{
	public:
		typedef std::vector<JSONType> container;
		typedef container::size_type size_type;
		typedef container::iterator iterator;
		typedef container::const_iterator const_iterator;

	private:
		container m_array;

	public:
		JSONArray(void);
		JSONArray(container array);
		JSONArray(const JSONArray &other);

		virtual
		~JSONArray(void);

		JSONArray&
		operator =(const JSONArray &other);

		JSONType&
		operator [](int n);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		bool
		empty(void);

		size_type
		size(void);

		void
		add(const JSONType &jsonType);

		JSONType&
		get(size_type index);

		iterator
		begin(void);

		const_iterator
		begin(void) const;

		iterator
		end(void);

		const_iterator
		end(void) const;
};

#endif /* JSONARRAY_HPP_ */
