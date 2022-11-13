/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Font.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:40:08 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 20:40:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_HPP_
# define FONT_HPP_

#include <engine/texture/Texture.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class Font
{
	public:
		SharedReference<Texture> atlas;

	public:
		Font(SharedReference<Texture> &atlas);

	public:
		virtual
		~Font();

	public:
		static Font&
		load(const std::string &path);

	public:
		static Font&
		consolas();
};

#endif /* FONT_HPP_ */
