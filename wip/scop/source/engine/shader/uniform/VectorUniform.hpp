/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorUniform.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORUNIFORM_HPP_
# define VECTORUNIFORM_HPP_

#include <engine/math/vector.hpp>
#include <engine/shader/ShaderVariable.hpp>
#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <string>

template<int N, typename T>
	class VectorUniform :
			public Uniform
	{
		public:
			VectorUniform(const std::string &name) :
					Uniform(name)
			{
			}

		public:
			void
			set(const Vector<N, T> &vector);
	};

#endif /* VECTORUNIFORM_HPP_ */
