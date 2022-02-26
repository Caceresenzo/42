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
#include <GL/glew.h>
#include <string>

class Text
{
	private:
		std::string m_value;
		Vector2f m_position;
		float m_size;
		bool m_invalidated;
		GLuint m_vertex_buffer_id;
		GLuint m_uv_buffer_id;

	public:
		Text(const std::string &initial = "", const Vector2f &position = Vector2f(), float size = 28);

		virtual
		~Text();

		void
		build();

		void
		invalidate();

		bool
		is_invalidated() const;

		const std::string&
		get() const;

		void
		set(const std::string &value);

		inline GLuint
		vertex_buffer_id()
		{
			return (m_vertex_buffer_id);
		}

		inline GLuint
		uv_buffer_id()
		{
			return (m_uv_buffer_id);
		}
};

#endif /* TEXT_HPP_ */
