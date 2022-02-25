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

#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>

class TextShader :
		public ShaderProgram
{
	public:
		SamplerUniform<int> sampler;

	public:
		TextShader();
		TextShader(const TextShader &other);

		virtual
		~TextShader();

		TextShader&
		operator=(const TextShader &other);

	protected:
		virtual void
		after_create();
};

#endif /* TEXTSHADER_HPP_ */
