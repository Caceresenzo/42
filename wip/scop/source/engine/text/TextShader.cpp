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
		ShaderProgram("assets/shaders/text/vertex.glsl", "assets/shaders/text/fragment.glsl"),
		window_size("windowSize"),
		texture_sampler("textureSampler"),
		position("in_Positions"),
		uv("in_UV")
{
	locate(window_size);
	locate(texture_sampler);
	locate(position);
	locate(uv);
}

TextShader::~TextShader()
{
}
