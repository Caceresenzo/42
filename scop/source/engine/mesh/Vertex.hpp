/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vertex.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:17:35 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/19 23:17:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_HPP_
# define VERTEX_HPP_

#include <engine/math/Vector.hpp>
#include <iterator>
#include <vector>

template<int N>
	struct Vertex
	{
		public:
			Vector<N, float> position;
			Vector<2, float> texture;

		public:
			static std::vector<Vertex>
			convert(const std::vector<Vector<N, float> > &positions, const std::vector<Vector<2, float> > &textures = std::vector<Vector<2, float> >())
			{
				std::vector<Vertex> vertexes;
				vertexes.reserve(positions.size());

				const size_t positions_size = positions.size();
				const size_t textures_size = textures.size();

				for (size_t index = 0; index < positions_size; ++index)
				{
					Vertex vertex;

					vertex.position = positions[index];

					if (index < textures_size)
						vertex.texture = textures[index];

					vertexes.push_back(vertex);
				}

				return (vertexes);
			}

	};

#endif /* VERTEX_HPP_ */
