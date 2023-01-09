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

#include <engine/text/Font.hpp>
#include <engine/text/TextMesh.hpp>
#include <engine/text/TextShader.hpp>
#include <lang/reference/SharedReference.hpp>
#include <util/function/Supplier.hpp>
#include <string>
#include <vector>

class TextRenderer
{
	public:
		SharedReference<TextShader> shader;

	public:
		TextRenderer(SharedReference<TextShader> &shader);

		virtual
		~TextRenderer();

	public:
		void
		render(SharedReference<TextMesh> &mesh);
};

#endif /* TEXTRENDERER_HPP_ */
