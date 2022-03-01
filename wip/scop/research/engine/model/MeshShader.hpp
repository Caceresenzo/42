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

#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <string>

class MeshShader :
		public ShaderProgram
{
	public:
		MatrixUniform<4, 4, float> model;
		MatrixUniform<4, 4, float> view;
		MatrixUniform<4, 4, float> projection;
		VectorAttribute<3, float> positions;

	public:
		MeshShader(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~MeshShader();

	public:
		static MeshShader*
		basic();
};

#endif /* MESHSHADER_HPP_ */
