/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshLoader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:40:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 22:40:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESHLOADER_HPP_
# define MESHLOADER_HPP_

#include <string>

class Mesh;

class MeshLoader
{
	public:
		MeshLoader();

		virtual
		~MeshLoader();

	public:
		void
		skip_face_remaining(std::istream &stream);

	public:
		Mesh*
		load(const std::string &path);
};

#endif /* MESHLOADER_HPP_ */
