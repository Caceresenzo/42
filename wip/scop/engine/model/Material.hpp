/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:36:41 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:36:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_HPP_
# define MATERIAL_HPP_

#include <engine/texture/Texture.hpp>
#include <lang/reference/SharedReference.hpp>

class Material
{
	public:
		SharedReference<Texture> texture;

	public:
		Material(SharedReference<Texture> texture);

		virtual
		~Material();
};

#endif /* MATERIAL_HPP_ */
