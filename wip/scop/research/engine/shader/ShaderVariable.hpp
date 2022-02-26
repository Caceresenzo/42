/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderVariable.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:25:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:25:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERVARIABLE_HPP_
# define SHADERVARIABLE_HPP_

#include <engine/opengl.hpp>
#include <GL/glew.h>
#include <string>

class ShaderProgram;

class ShaderVariable
{
	private:
		std::string m_name;
		GLint m_location;

	protected:
		ShaderVariable(const std::string &name);

		virtual
		~ShaderVariable();

	public:
		void
		locate(const ShaderProgram &program);

	protected:
		virtual GLint
		find_location(GLuint program_id, const char *name) const = 0;

	public:
		inline const std::string&
		name() const
		{
			return (m_name);
		}

		inline GLint
		location() const
		{
			return (m_location);
		}
};

#endif /* SHADERVARIABLE_HPP_ */
