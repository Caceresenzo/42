/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonStructure.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:18:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 15:18:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONSTRUCTURE_HPP_
# define JSONSTRUCTURE_HPP_

#include <util/json/JsonValue.hpp>

class JsonStructure :
		public JsonValue
{
	public:
		virtual
		~JsonStructure(void)
		{
		}

		virtual void
		clear(void) = 0;
};

#endif /* JSONSTRUCTURE_HPP_ */
