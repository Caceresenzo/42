/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:31:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:31:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTRENDERER_HPP_
# define TEXTRENDERER_HPP_

#include <engine/text/Text.hpp>
#include <engine/text/TextShader.hpp>
#include <vector>

class Texture;

class TextShader;

class TextRenderer
{
	public:
		TextShader *shader;
		Texture *font_altas;

	public:
		TextRenderer();

		virtual
		~TextRenderer();

		void
		render(const std::vector<Text*> texts) const;

		void
		render(Text &text) const;
};

#endif /* TEXTRENDERER_HPP_ */
