/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextShader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:29:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTSHADER_HPP_
# define TEXTSHADER_HPP_

#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/VectorUniform.hpp>

class TextShader :
		public ShaderProgram
{
	public:
		VectorUniform<2, int> window_size;
		SamplerUniform<int> texture_sampler;
		VectorAttribute<2, float> position;
		VectorAttribute<2, float> uv;

	public:
		TextShader();

		virtual
		~TextShader();
};

#endif /* TEXTSHADER_HPP_ */
