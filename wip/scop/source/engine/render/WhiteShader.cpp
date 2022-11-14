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

#include <engine/render/WhiteShader.hpp>

WhiteShader::WhiteShader(const std::string &vertex_file, const std::string &fragment_file) :
		Program(vertex_file, fragment_file),
		model("model"),
		view("view"),
		projection("projection"),
		positions("in_Positions")
{
	locate(model);
	locate(view);
	locate(projection);
	locate(positions);
}

WhiteShader::~WhiteShader()
{
}

WhiteShader*
WhiteShader::from_assets()
{
	return (new WhiteShader("assets/shaders/model/white/vertex.glsl", "assets/shaders/model/white/fragment.glsl"));
}
