/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorAttribute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:34:52 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:34:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/attribute/Vector3Attribute.hpp>
#include <engine/shader/attribute/Vector2Attribute.hpp>

template<>
	const GLuint Vector3Attribute<float>::DATA_TYPE = GL_FLOAT;

template<>
	const GLuint Vector2Attribute<float>::DATA_TYPE = GL_FLOAT;
