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

#include <engine/math/Vector.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/shader/Program.hpp>
#include <engine/shader/Uniform.hpp>

class TextShader :
		public Program
{
	public:
		Uniform<Vector<2, int>> window_size;
		Uniform<int> texture_sampler;
		Attribute<Vector<2, float>> position;
		Attribute<Vector<2, float>> uv;

	public:
		TextShader(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~TextShader();

	public:
		static TextShader*
		basic();
};

#endif /* TEXTSHADER_HPP_ */
