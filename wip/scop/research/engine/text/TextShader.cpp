/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextShader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:29:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/text/TextShader.hpp>

TextShader::TextShader() :
		ShaderProgram("text-vertex.glsl", "text-fragment.glsl"),
		sampler("myTextureSampler")
{
	locate(sampler);
}

TextShader::~TextShader()
{
}

TextShader::TextShader(const TextShader &other) :
		ShaderProgram(other),
		sampler(other.sampler)
{
}

TextShader&
TextShader::operator=(const TextShader &other)
{
	if (this != &other)
	{
		sampler = other.sampler;
	}

	return (*this);
}

void
TextShader::after_create()
{
	locate(sampler);
}
