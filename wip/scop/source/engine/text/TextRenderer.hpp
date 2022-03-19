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

#include <engine/scene/Component.hpp>
#include <engine/text/Font.hpp>
#include <engine/text/Text.hpp>
#include <engine/text/TextShader.hpp>
#include <lang/reference/SharedReference.hpp>
#include <util/function/Supplier.hpp>
#include <string>
#include <vector>

class TextRenderer :
		public Component
{
	public:
		static std::string NAME;

	public:
		SharedReference<TextShader> shader;
		SharedReference<Font> font;
		SharedReference<Text> text;
		SharedReference<Supplier<std::string> > updater;

	public:
		TextRenderer(GameObject &parent);

		virtual
		~TextRenderer();

	public:
		virtual void
		render();
};

#endif /* TEXTRENDERER_HPP_ */
