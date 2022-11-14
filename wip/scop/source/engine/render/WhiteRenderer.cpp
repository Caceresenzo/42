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
#include <engine/math/vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/model/Model.hpp>
#include <engine/render/WhiteRenderer.hpp>
#include <engine/render/WhiteShader.hpp>
#include <engine/shader/Uniform.hpp>
#include <engine/texture/Texture.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lang/Math.hpp>

WhiteRenderer::WhiteRenderer(SharedReference<WhiteShader> &shader, SharedReference<PerspectiveCamera> &camera) :
	shader(shader),
	camera(camera)
{
}

WhiteRenderer::~WhiteRenderer()
{
}

void
WhiteRenderer::render(SharedReference<Model> &model)
{
	if (!shader || !camera)
		return;

	Vector<2, int> size = Window::current().size();
	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), float(size.x) / float(size.y), 0.1f, 10000.0f);

	shader->use();

	shader->projection.set(projection);
	shader->view.set(camera->view_matrix());
	shader->model.set(model->transform.model());

	model->vertex_buffer_array->bind(true);

	model->vertex_buffer_array->get(1)->bind();
	shader->positions.link();
	shader->positions.enable();

	glDrawElements(model->mesh->mode, model->mesh->indices.size(), GL_UNSIGNED_INT, NULL);

	model->vertex_buffer_array->unbind(true);

	shader->positions.disable();

	shader->unuse();
}
