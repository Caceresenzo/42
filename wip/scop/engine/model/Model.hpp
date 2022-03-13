/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:36:55 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:36:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP_
# define MODEL_HPP_

#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/Material.hpp>
#include <lang/reference/SharedReference.hpp>

class Model
{
	public:
		SharedReference<Mesh> mesh;
		SharedReference<Material> material;

	public:
		Model(SharedReference<Mesh> mesh);
		Model(SharedReference<Mesh> mesh, SharedReference<Material> material);

		virtual
		~Model();
};

#endif /* MODEL_HPP_ */
