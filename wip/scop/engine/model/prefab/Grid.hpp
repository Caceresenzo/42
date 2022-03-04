/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:23:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/04 00:23:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_HPP_
# define GRID_HPP_

#include <engine/model/Mesh.hpp>

class Mesh;

class Grid
{
	public:
		static Mesh*
		of(int slices);
};

#endif /* GRID_HPP_ */
