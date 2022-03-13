/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Component.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:16:50 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:16:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

#include <engine/math/Transform.hpp>
#include <engine/scene/GameObject.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>

class GameObject;

class Component
{
	public:
		GameObject &parent;
		std::string name;

	public:
		Component(GameObject &parent, const std::string &name);

		virtual
		~Component();

	public:
		virtual void
		update();

		virtual void
		render();

	public:
		Transform<float>&
		transform();
};

#endif /* COMPONENT_HPP_ */
