/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:54:12 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 14:54:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_HPP_
# define OPENGL_HPP_

#define GLEW_STATIC
# include <GL/glew.h>
# include <GL/freeglut.h>
# include <GL/gl.h>
# include <GLFW/glfw3.h>
# include <iterator>

template<typename T>
	struct GLType
	{
			static const GLenum DATA_TYPE;
	};

class OpenGL
{
	public:
		static void
		message_callback(GLenum source, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar *message, const void*);

		static void
		check_error();

		static void
		print_basic_info();
};

#endif /* OPENGL_HPP_ */
