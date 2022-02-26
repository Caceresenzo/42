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

#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/texture/Texture.hpp>
#include <GL/glew.h>
#include <iterator>
#include <string>
#include <vector>

TextRenderer::TextRenderer() :
		shader(NULL),
		font_altas(NULL)
{
	ImageData *image_data = NULL;

	try
	{
		shader = new TextShader();

		BMPImageLoader loader;
		image_data = loader.load("font.bmp");

		font_altas = Texture::from_image(image_data);

		delete image_data;
		image_data = NULL;

	}
	catch (...)
	{
		if (shader)
			delete shader;

		if (image_data)
			delete image_data;

		if (font_altas)
			delete font_altas;

		throw;
	}
}

TextRenderer::~TextRenderer()
{
	delete shader;
}

void
TextRenderer::render(std::vector<Text*> texts) const
{
	typedef typename std::vector<Text*>::const_iterator const_iterator;

	for (const_iterator iterator = texts.begin(); iterator < texts.end(); ++iterator)
	{
		Text *text = *iterator;

		if (text)
			this->render(*text);
	}
}

void
TextRenderer::render(Text &text) const
{
	if (text.is_invalidated())
		text.build();

	shader->use();
	font_altas->set_active(0);
	font_altas->bind();
	shader->sampler.set(0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, text.vertex_buffer_id());
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, text.uv_buffer_id());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, text.get().size() * 6);

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
