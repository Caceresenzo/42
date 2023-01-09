/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:31:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:31:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Window.hpp>
#include <engine/math/Vector.hpp>
#include <engine/opengl.hpp>
#include <engine/shader/Uniform.hpp>
#include <engine/text/Font.hpp>
#include <engine/text/TextMesh.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lang/reference/SharedReference.hpp>

TextRenderer::TextRenderer(SharedReference<TextShader> &shader) :
	shader(shader)
{
}

TextRenderer::~TextRenderer()
{
}

void
TextRenderer::render(SharedReference<TextMesh> &mesh)
{
	shader->use();
	mesh->font->atlas->set_active(0);

	Vector<2, int> size = Window::current().size();
	shader->window_size.set(size);
	shader->texture_sampler.set(0);

	mesh->vertex_array_object->bind();
	mesh->vertex_buffer_object->bind();

	shader->position.enable();
	shader->position.link(sizeof(Vertex<2> ), (void*)offsetof(Vertex<2>, position));

	shader->uv.enable();
	shader->uv.link(sizeof(Vertex<2> ), (void*)offsetof(Vertex<2>, texture));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthRange(0, 0.01);
	glDrawArrays(GL_TRIANGLES, 0, mesh->triangle_count);
	glDepthRange(0, 1.0);
	glDisable(GL_BLEND);

	shader->uv.disable();
	shader->position.disable();

	mesh->vertex_buffer_object->unbind();
	mesh->vertex_array_object->unbind();

	mesh->font->atlas->unbind();
}
