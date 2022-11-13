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

#ifndef MESHSHADER_HPP_
# define MESHSHADER_HPP_

#include <engine/math/vector.hpp>
#include <engine/math/matrix.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/shader/Program.hpp>
#include <engine/shader/Uniform.hpp>
#include <string>

class MeshShader :
		public Program
{
	public:
		Uniform<Matrix<4, 4, float>> model;
		Uniform<Matrix<4, 4, float>> view;
		Uniform<Matrix<4, 4, float>> projection;
		Uniform<bool> use_texture;
		Uniform<int> texture_sampler;
		Attribute<Vector<2, float>> texture_positions;
		Attribute<Vector<3, float>> positions;

	public:
		MeshShader(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~MeshShader();

	public:
		static MeshShader*
		basic();
};

#endif /* MESHSHADER_HPP_ */
