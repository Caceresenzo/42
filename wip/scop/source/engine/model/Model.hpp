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
		std::vector<SharedReference<Texture>> textures;
		SharedReference<VertexArrayObject> vertex_buffer_array;

	public:
		Model(SharedReference<Mesh> mesh, std::vector<SharedReference<Texture> > textures = std::vector<SharedReference<Texture> >());

		virtual
		~Model();
};

#endif /* MODEL_HPP_ */
