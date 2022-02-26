/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2Attribute.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:34:52 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:34:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2ATTRIBUTE_HPP_
# define VECTOR2ATTRIBUTE_HPP_

#include <engine/shader/attribute/Attribute.hpp>

template<typename T>
	class Vector2Attribute :
			public Attribute
	{
		private:
			static const GLuint DATA_TYPE;

		public:
			Vector2Attribute(const std::string &name) :
					Attribute(name, 2, DATA_TYPE, false)
			{
			}

			virtual
			~Vector2Attribute()
			{
			}
	};

#endif /* VECTOR2ATTRIBUTE_HPP_ */
