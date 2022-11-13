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

TextRenderer::TextRenderer(SharedReference<TextShader> &shader, SharedReference<Font> &font) :
	shader(shader),
	font(font)
{
}

TextRenderer::~TextRenderer()
{
}

void
TextRenderer::render(TextMesh &mesh)
{
	shader->use();
	font->atlas->set_active(0);
	font->atlas->bind();

	Vector<2, int> size = Window::current().size();
	shader->window_size.set(size);
	shader->texture_sampler.set(0);

	mesh.vertex_array().bind(false);

	shader->position.enable();
	mesh.vertex_buffer().bind();
	shader->position.link();

	shader->uv.enable();
	mesh.uv_buffer().bind();
	shader->uv.link();

	glDepthRange(0, 0.01);
	glDrawArrays(GL_TRIANGLES, 0, mesh.get().size() * 6);
	glDepthRange(0, 1.0);

	shader->position.disable();
	shader->uv.disable();

	mesh.vertex_array().unbind();
	mesh.vertex_buffer().unbind();
	mesh.uv_buffer().unbind();

	font->atlas->unbind();
}
