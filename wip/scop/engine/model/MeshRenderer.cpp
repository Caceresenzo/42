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

#include <engine/model/MeshRenderer.hpp>

std::string MeshRenderer::NAME = "mesh-renderer";

MeshRenderer::MeshRenderer(GameObject &parent) :
		Component(parent, NAME)
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

	int width = 0, height = 0;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), float(width) / float(height), 0.1f, 10000.0f);

	shader->use();

	shader->projection.set(projection);
	shader->view.set(camera->view_matrix());
	shader->model.set(transform().model());

	model->mesh->render(*shader);

	shader->unuse();
}
