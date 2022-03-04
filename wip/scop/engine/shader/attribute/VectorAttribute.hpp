/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorAttribute.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:34:52 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:34:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORATTRIBUTE_HPP_
# define VECTORATTRIBUTE_HPP_

#include <engine/opengl.hpp>
#include <engine/shader/attribute/Attribute.hpp>
#include <string>

template<int N, typename T>
	class VectorAttribute :
			public Attribute
	{
		public:
			VectorAttribute(const std::string &name) :
					Attribute(name, N, GLType<T>::DATA_TYPE, false)
			{
			}

			virtual
			~VectorAttribute()
			{
			}
	};

#endif /* VECTORATTRIBUTE_HPP_ */
