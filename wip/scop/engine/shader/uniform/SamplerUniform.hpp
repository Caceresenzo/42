/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SamplerUniform.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:24:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 00:24:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLERUNIFORM_HPP_
# define SAMPLERUNIFORM_HPP_

#include <engine/math/matrix.hpp>
#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <string>

template<typename T>
	class SamplerUniform :
			public Uniform
	{
		public:
			SamplerUniform(const std::string &name) :
					Uniform(name)
			{
			}

		public:
			void
			set(const T &sampler);
	};

#endif /* SAMPLERUNIFORM_HPP_ */
