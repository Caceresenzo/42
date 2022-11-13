/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshRenderer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:53:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:53:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESHRENDERER_HPP_
# define MESHRENDERER_HPP_

#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/mesh/MeshShader.hpp>
#include <engine/math/Transform.hpp>
#include <engine/mesh/Mesh.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class MeshRenderer
{
	public:
		SharedReference<MeshShader> shader;
		SharedReference<PerspectiveCamera> camera;
		bool no_depth;

	public:
		MeshRenderer(SharedReference<MeshShader> &shader, SharedReference<PerspectiveCamera> &camera);

		virtual
		~MeshRenderer();

	public:
		void
		render(const Transform<float> &transform, const Mesh &mesh);
};

#endif /* MESHRENDERER_HPP_ */
