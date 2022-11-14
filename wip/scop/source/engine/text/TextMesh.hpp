/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Text.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:24:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:24:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTMESH_HPP_
# define TEXTMESH_HPP_

#include <engine/math/vector.hpp>
#include <engine/text/Font.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class TextMesh
{
	public:
		SharedReference<Font> font;
		std::string value;
		Vector<2, float> position;
		float size;
		SharedReference<VertexArrayObject> vertex_array;
		SharedReference<VertexBufferObject> vertex_buffer;
		SharedReference<VertexBufferObject> uv_buffer;

	public:
		TextMesh(SharedReference<Font> &font, const std::string &initial = "", const Vector<2, float> &position = Vector<2, float>(), float size = 28);

		virtual
		~TextMesh();

		void
		build();

		void
		set(const std::string &value);
};

#endif /* TEXTMESH_HPP_ */
