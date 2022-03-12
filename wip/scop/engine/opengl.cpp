/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:03:09 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 20:03:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/opengl.hpp>
#include <cstdio>
#include <map>
#include <string>

template<>
	const GLenum GLType<float>::DATA_TYPE = GL_FLOAT;

void
OpenGL::message_callback(GLenum source, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar *message, const void*)
{
	static std::map<int, std::string> _debug_types;

	if (_debug_types.empty())
	{
		_debug_types[GL_DEBUG_SOURCE_API] = "API";
		_debug_types[GL_DEBUG_SOURCE_WINDOW_SYSTEM] = "WINDOW_SYSTEM";
		_debug_types[GL_DEBUG_SOURCE_SHADER_COMPILER] = "SHADER_COMPILER";
		_debug_types[GL_DEBUG_SOURCE_THIRD_PARTY] = "THIRD_PARTY";
		_debug_types[GL_DEBUG_SOURCE_APPLICATION] = "APPLICATION";
		_debug_types[GL_DEBUG_SOURCE_OTHER] = "OTHER";
		_debug_types[GL_DEBUG_TYPE_ERROR] = "ERROR";
		_debug_types[GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR] = "DEPRECATED_BEHAVIOR";
		_debug_types[GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR] = "UNDEFINED_BEHAVIOR";
		_debug_types[GL_DEBUG_TYPE_PORTABILITY] = "PORTABILITY";
		_debug_types[GL_DEBUG_TYPE_PERFORMANCE] = "PERFORMANCE";
		_debug_types[GL_DEBUG_TYPE_OTHER] = "OTHER";
		_debug_types[GL_DEBUG_TYPE_MARKER] = "MARKER";
		_debug_types[GL_DEBUG_TYPE_POP_GROUP] = "POP_GROUP";
		_debug_types[GL_DEBUG_SEVERITY_NOTIFICATION] = "NOTIFICATION";
	}

	if (GL_DEBUG_TYPE_OTHER == type)
		return;

	fprintf(stderr, "[%s] [%s] [%s] %s\n", (_debug_types[severity].c_str()), (_debug_types[source].c_str()), (_debug_types[type].c_str()), message);
}
