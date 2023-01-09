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

#ifndef WHITESHADER_HPP_
# define WHITESHADER_HPP_

#include <engine/math/Matrix.hpp>
#include <engine/math/Vector.hpp>
#include <engine/shader/Attribute.hpp>
#include <engine/shader/Program.hpp>
#include <engine/shader/Uniform.hpp>
#include <string>

class WhiteShader :
		public Program
{
	public:
		Uniform<Matrix<4, 4, float>> model;
		Uniform<Matrix<4, 4, float>> view;
		Uniform<Matrix<4, 4, float>> projection;
		Attribute<Vector<3, float>> positions;

	public:
		WhiteShader(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~WhiteShader();

	public:
		static WhiteShader*
		from_assets();
};

#endif /* WHITESHADER_HPP_ */
