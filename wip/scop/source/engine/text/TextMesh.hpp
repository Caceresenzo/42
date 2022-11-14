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
	private:
		SharedReference<Font> m_font;
		std::string m_value;
		Vector<2, float> m_position;
		float m_size;
		bool m_invalidated;
		VertexArrayObject m_vertex_array;
		VertexBufferObject m_vertex_buffer;
		VertexBufferObject m_uv_buffer;

	public:
		TextMesh(SharedReference<Font> &font, const std::string &initial = "", const Vector<2, float> &position = Vector<2, float>(), float size = 28);

		virtual
		~TextMesh();

		void
		build();

		void
		invalidate();

		void
		set(const std::string &value);

		void
		set_and_build(const std::string &value);

	public:
		inline bool
		is_invalidated() const
		{
			return (m_invalidated);
		}

		inline const std::string&
		get() const
		{
			return (m_value);
		}

		inline SharedReference<Font>
		font()
		{
			return (m_font);
		}

		inline VertexArrayObject&
		vertex_array()
		{
			return (m_vertex_array);
		}

		inline VertexBufferObject&
		vertex_buffer()
		{
			return (m_vertex_buffer);
		}

		inline VertexBufferObject&
		uv_buffer()
		{
			return (m_uv_buffer);
		}
};

#endif /* TEXTMESH_HPP_ */
