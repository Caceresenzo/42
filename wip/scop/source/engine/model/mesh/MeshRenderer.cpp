/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:53:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:53:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Window.hpp>
#include <engine/math/matrix.hpp>
#include <engine/math/Transform.hpp>
#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/mesh/MeshRenderer.hpp>
#include <engine/model/mesh/MeshShader.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lang/Math.hpp>

std::string MeshRenderer::NAME = "mesh-renderer";

MeshRenderer::MeshRenderer(GameObject &parent) :
		Component(parent, NAME),
		no_depth(false)
{
}

MeshRenderer::~MeshRenderer()
{
}

void
MeshRenderer::render()
{
	if (!shader || !model || !camera)
		return;

	Vector<2, int> size = Window::current().size();
	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), float(size.x) / float(size.y), 0.1f, 10000.0f);

	shader->use();

	shader->projection.set(projection);
	shader->view.set(camera->view_matrix());
	shader->model.set(transform().model());

	if (no_depth)
		glDepthRange(0, 0.01);

	model->mesh->render(*shader);

	if (no_depth)
		glDepthRange(0, 1.0);

	shader->unuse();
}
