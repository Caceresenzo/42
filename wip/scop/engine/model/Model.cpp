/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:36:55 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:36:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/model/Model.hpp>

Model::Model(SharedReference<Mesh> mesh) :
		mesh(mesh),
		material()
{
}

Model::Model(SharedReference<Mesh> mesh, SharedReference<Material> material) :
		mesh(mesh),
		material(material)
{
}

Model::~Model()
{
}

