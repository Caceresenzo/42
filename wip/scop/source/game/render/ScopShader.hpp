/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshShader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 23:34:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPSHADER_HPP_
# define SCOPSHADER_HPP_

#include <engine/math/Matrix.hpp>
#include <engine/math/Vector.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/shader/Program.hpp>
#include <engine/shader/Uniform.hpp>
#include <string>

class ScopShader :
		public Program
{
	public:
		Attribute<Vector<3, float>> positions;
		Attribute<Vector<2, float>> textures;
		Uniform<Matrix<4, 4, float>> model;
		Uniform<Matrix<4, 4, float>> view;
		Uniform<Matrix<4, 4, float>> projection;
		Uniform<bool> use_texture;
		Uniform<int> texture_sampler;
		Uniform<float> transition;

	public:
		ScopShader(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~ScopShader();

	public:
		static ScopShader*
		from_assets();
};

#endif /* SCOPSHADER_HPP_ */
