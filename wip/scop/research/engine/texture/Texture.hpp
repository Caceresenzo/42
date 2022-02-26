/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:24:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 19:24:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

#include <engine/opengl.hpp>
#include <GL/glew.h>

class ImageData;

class Texture
{
	private:
		GLuint m_id;

	public:
		Texture();

		virtual
		~Texture();

	public:
		void
		set_active(int unit = 0);

		void
		bind();

		void
		unbind();

	public:
		static Texture*
		from_image(ImageData *image_data);
};

#endif /* TEXTURE_HPP_ */
