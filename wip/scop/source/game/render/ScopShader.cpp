/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshShader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 23:34:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/render/ScopShader.hpp>

ScopShader::ScopShader(const std::string &vertex_file, const std::string &fragment_file) :
	Program(vertex_file, fragment_file),
	positions("in_Positions"),
	texture_positions("in_TextureCoordinates"),
	model("model"),
	view("view"),
	projection("projection"),
	use_texture("useTexture"),
	texture_sampler("textureSampler")
{
	locate(positions);
	locate(texture_positions);
	locate(model);
	locate(view);
	locate(projection);
	locate(use_texture);
	locate(texture_sampler);
}

ScopShader::~ScopShader()
{
}

ScopShader*
ScopShader::from_assets()
{
	return (new ScopShader("assets/shaders/model/scop/vertex.glsl", "assets/shaders/model/scop/fragment.glsl"));
}
