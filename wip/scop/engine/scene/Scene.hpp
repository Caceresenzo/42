/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:12:04 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 02:12:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP_
# define SCENE_HPP_

#include <engine/scene/Node.hpp>

class Scene :
		public Node
{
	public:
		Scene();

		virtual
		~Scene();
};

#endif /* SCENE_HPP_ */
