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

#ifndef SCOPRENDERER_HPP_
# define SCOPRENDERER_HPP_

#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/math/Transform.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/model/Model.hpp>
#include <game/render/ScopShader.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class Model;

class ScopRenderer
{
	public:
		SharedReference<ScopShader> shader;
		SharedReference<PerspectiveCamera> camera;

	public:
		ScopRenderer(SharedReference<ScopShader> &shader, SharedReference<PerspectiveCamera> &camera);

		virtual
		~ScopRenderer();

	public:
		void
		render(SharedReference<Model> &model);
};

#endif /* SCOPRENDERER_HPP_ */
