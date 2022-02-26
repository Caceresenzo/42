/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3Attribute.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:34:52 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:34:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3ATTRIBUTE_HPP_
# define VECTOR3ATTRIBUTE_HPP_

#include <engine/shader/attribute/Attribute.hpp>

template<typename T>
	class Vector3Attribute :
			public Attribute
	{
		private:
			static const GLuint DATA_TYPE;

		public:
			Vector3Attribute(const std::string &name) :
					Attribute(name, 3, DATA_TYPE, false)
			{
			}

			virtual
			~Vector3Attribute()
			{
			}
	};

#endif /* VECTOR3ATTRIBUTE_HPP_ */
