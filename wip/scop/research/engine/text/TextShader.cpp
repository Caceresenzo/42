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
		sampler("myTextureSampler"),
		position("vertexPosition_screenspace"),
		uv("vertexUV")
{
	locate(sampler);
	locate(position);
	locate(uv);
}

TextShader::~TextShader()
{
}
