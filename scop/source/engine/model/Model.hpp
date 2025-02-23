/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:08:20 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 16:08:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP_
# define MODEL_HPP_

#include <engine/math/Transform.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <lang/reference/SharedReference.hpp>
#include <vector>

class Model
{
	public:
		Transform<float> transform;
		SharedReference<Mesh> mesh;
		SharedReference<Texture> texture;

	public:
		Model(SharedReference<Mesh> mesh);
		Model(SharedReference<Mesh> mesh, SharedReference<Texture> texture);

		virtual
		~Model();
};

#endif /* MODEL_HPP_ */
