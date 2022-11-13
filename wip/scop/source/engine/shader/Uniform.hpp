/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uniform.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:47:18 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:47:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIFORM_HPP_
# define UNIFORM_HPP_

#include <engine/opengl.hpp>
#include <engine/shader/Variable.hpp>
#include <string>

template<typename T>
	class Uniform :
		public Variable
	{
		public:
			Uniform(const std::string &name) :
				Variable(name)
			{
			}

			virtual
			~Uniform()
			{
			}

		protected:
			virtual GLint
			find_location(GLuint program_id, const char *name) const
			{
				return (glGetUniformLocation(program_id, name));
			}

		public:
			void set(const T &value);
	};

#endif /* UNIFORM_HPP_ */
