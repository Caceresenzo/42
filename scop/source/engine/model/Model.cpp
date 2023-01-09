/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:08:20 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 16:08:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/model/Model.hpp>

Model::Model(SharedReference<Mesh> mesh) :
	mesh(mesh)
{
}

Model::Model(SharedReference<Mesh> mesh, SharedReference<Texture> texture) :
	mesh(mesh),
	texture(texture)
{
}

Model::~Model()
{
}
