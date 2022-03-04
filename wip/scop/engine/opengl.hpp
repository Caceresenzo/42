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

template<typename T>
	struct GLType
	{
		static const GLenum DATA_TYPE;
	};

#endif /* OPENGL_HPP_ */
