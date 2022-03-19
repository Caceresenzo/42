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
	private:
		SharedReference<Texture> m_atlas;

	public:
		Font(const std::string &font_atlas_file);
		Font(SharedReference<Texture> &atlas);

		virtual
		~Font();

	public:
		inline Texture&
		atlas()
		{
			return (*m_atlas);
		}

	public:
		static Font&
		consolas();
};

#endif /* FONT_HPP_ */
