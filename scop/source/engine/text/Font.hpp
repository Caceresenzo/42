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

#include <engine/math/Vector.hpp>
#include <engine/texture/Texture.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class Font
{
	public:
		SharedReference<Texture> atlas;
		Vector<2, float> character_dimension;

	public:
		Font(SharedReference<Texture> &atlas, const Vector<2, float> &character_dimension);

	public:
		virtual
		~Font();

	public:
		static SharedReference<Font>
		load(const std::string &path, const Vector<2, float> &character_dimension);

	public:
		static SharedReference<Font>
		consolas();
};

#endif /* FONT_HPP_ */
