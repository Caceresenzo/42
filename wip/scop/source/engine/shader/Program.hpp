/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:59:49 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:59:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_HPP_
# define PROGRAM_HPP_

#include <engine/opengl.hpp>
#include <GL/glew.h>
#include <string>

class Variable;

class Program
{
	public:
		static const GLuint UNDEFINED_VALUE;

	private:
		GLuint m_id;

	public:
		Program(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~Program();

		void
		use();

		void
		unuse();

		void
		locate(Variable &variable) const;

	public:
		GLuint
		id() const;
};

#endif /* PROGRAM_HPP_ */
