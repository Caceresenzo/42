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
#include <engine/math/vector.hpp>
#include <engine/opengl.hpp>
#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/VectorUniform.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string TextRenderer::NAME = "text-renderer";

TextRenderer::TextRenderer(GameObject &parent) :
		Component(parent, NAME),
		shader(),
		font()
{
}

TextRenderer::~TextRenderer()
{
}

void
TextRenderer::render()
{
	if (!text || !shader || !font)
		return;

	if (updater)
		text->set(updater->get());

	if (text->is_invalidated())
		text->build();

	shader->use();
	font->atlas().set_active(0);
	font->atlas().bind();

	Vector<2, int> size = Window::current().size();
	shader->window_size.set(size);
	shader->texture_sampler.set(0);

	text->vertex_array().bind(false);

	shader->position.enable();
	text->vertex_buffer().bind();
	shader->position.link();

	shader->uv.enable();
	text->uv_buffer().bind();
	shader->uv.link();

	glDrawArrays(GL_TRIANGLES, 0, text->get().size() * 6);

	shader->position.disable();
	shader->uv.disable();

	text->vertex_array().unbind();
	text->vertex_buffer().unbind();
	text->uv_buffer().unbind();

	font->atlas().unbind();
}
