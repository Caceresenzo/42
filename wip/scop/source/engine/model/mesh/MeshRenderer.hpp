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
#include <engine/model/mesh/MeshShader.hpp>
#include <engine/model/Model.hpp>
#include <engine/scene/Component.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class MeshRenderer :
		public Component
{
	public:
		static std::string NAME;

	public:
		SharedReference<PerspectiveCamera> camera;
		SharedReference<MeshShader> shader;
		SharedReference<Model> model;
		bool no_depth;

	public:
		MeshRenderer(GameObject &parent);

		virtual
		~MeshRenderer();

	public:
		virtual void
		render();
};

#endif /* MESHRENDERER_HPP_ */
