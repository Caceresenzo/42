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

#ifndef TEXT_HPP_
# define TEXT_HPP_

#include <engine/math/vector.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/glew.h>
#include <string>

class Text
{
	private:
		std::string m_value;
		Vector2f m_position;
		float m_size;
		bool m_invalidated;
		VertexBufferObject m_vertex_buffer;
		VertexBufferObject m_uv_buffer;

	public:
		Text(const std::string &initial = "", const Vector2f &position = Vector2f(), float size = 28);

		virtual
		~Text();

		void
		build();

		void
		invalidate();

		void
		set(const std::string &value);

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

#endif /* TEXT_HPP_ */
