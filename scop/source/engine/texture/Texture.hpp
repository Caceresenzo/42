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
#include <lang/image/ImageData.hpp>
#include <lang/reference/SharedReference.hpp>

class Texture
{
	public:
		std::string name;

	private:
		GLuint m_id;

	public:
		Texture(const std::string &name);

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
		static SharedReference<Texture>
		from_image(const std::string &name, SharedReference<ImageData> image_data);

	private:
		static GLint
		to_format(ImageData::Format format);

		static GLint
		to_internal_format(ImageData::Format format);
};

#endif /* TEXTURE_HPP_ */
