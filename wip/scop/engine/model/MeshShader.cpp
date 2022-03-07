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

#include <engine/model/MeshShader.hpp>

MeshShader::MeshShader(const std::string &vertex_file, const std::string &fragment_file) :
		ShaderProgram(vertex_file, fragment_file),
		model("model"),
		view("view"),
		projection("projection"),
		use_texture("useTexture"),
		texture_sampler("textureSampler"),
		texture_positions("in_TextureCoordinates"),
		positions("in_Positions")
{
	locate(model);
	locate(view);
	locate(projection);
	locate(use_texture);
	locate(texture_sampler);
	locate(texture_positions);
	locate(positions);
}

MeshShader::~MeshShader()
{
}

MeshShader*
MeshShader::basic()
{
	return (new MeshShader("model-vertex.glsl", "model-fragment.glsl"));
}
