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
#include <engine/render/WhiteShader.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/shader/Uniform.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <game/render/ScopRenderer.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lang/Math.hpp>
#include <vector>

ScopRenderer::ScopRenderer(SharedReference<ScopShader> &shader, SharedReference<PerspectiveCamera> &camera) :
	shader(shader),
	camera(camera)
{
}

ScopRenderer::~ScopRenderer()
{
}

void
ScopRenderer::render(SharedReference<Model> &model)
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

	if (!model->textures.empty())
	{
		shader->use_texture.set(true);

		model->vertex_buffer_array->get(2)->bind();
		shader->texture_positions.link();
		shader->texture_positions.enable();

		SharedReference<Texture> &texture = model->textures.front();

		texture->set_active(0);
		texture->bind();
		shader->texture_sampler.set(0);
	}
	else
		shader->use_texture.set(false);

	glDrawElements(model->mesh->mode, model->mesh->indices.size(), GL_UNSIGNED_INT, NULL);

	if (!model->textures.empty())
	{
		SharedReference<Texture> &texture = model->textures.front();

		texture->set_active(0);
		texture->unbind();
		shader->texture_positions.disable();
	}

	model->vertex_buffer_array->unbind(true);

	shader->positions.disable();

	shader->unuse();
}
