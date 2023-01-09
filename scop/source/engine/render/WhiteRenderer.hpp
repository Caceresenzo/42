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

#ifndef WHITERENDERER_HPP_
# define WHITERENDERER_HPP_

#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/math/Transform.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/render/WhiteShader.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class Model;

class WhiteRenderer
{
	public:
		SharedReference<WhiteShader> shader;
		SharedReference<PerspectiveCamera> camera;

	public:
		WhiteRenderer(SharedReference<WhiteShader> &shader, SharedReference<PerspectiveCamera> &camera);

		virtual
		~WhiteRenderer();

	public:
		void
		render(SharedReference<Model> &model);
};

#endif /* WHITERENDERER_HPP_ */
