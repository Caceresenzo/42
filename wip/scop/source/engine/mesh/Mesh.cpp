/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:40:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 20:40:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/mesh/Mesh.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <stddef.h>
#include <queue>
#include <utility>

Mesh::Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<Vector<2, float> > &textures, const std::vector<unsigned int> &indices, Mode mode) :
	vertices(vertices),
	textures(textures),
	indices(indices),
	mode(mode)
{
}

Mesh::~Mesh()
{
}

void
Mesh::align(Vector<3, float> center)
{
	if (center == Vector<3, float>::ZERO)
		return;

	typedef std::vector<Vector<3, float> >::iterator iterator;
	for (iterator it = vertices.begin(); it < vertices.end(); ++it)
		*it -= center;
}

BoundingBox<3, float>
Mesh::compute_bounding_box() const
{
	if (vertices.empty())
		return (BoundingBox<3, float>(0, 0));

	Vector<3, float> lower(std::numeric_limits<float>::max());
	Vector<3, float> higher(std::numeric_limits<float>::min());

	typedef std::vector<Vector<3, float> >::const_iterator iterator;
	for (iterator it = vertices.begin(); it < vertices.end(); ++it)
	{
		const Vector<3, float> &vector = *it;

		lower.x = Math::min(lower.x, vector.x);
		lower.y = Math::min(lower.y, vector.y);
		lower.z = Math::min(lower.z, vector.z);

		higher.x = Math::max(higher.x, vector.x);
		higher.y = Math::max(higher.y, vector.y);
		higher.z = Math::max(higher.z, vector.z);
	}

	return (BoundingBox<3, float>(lower, higher));
}
