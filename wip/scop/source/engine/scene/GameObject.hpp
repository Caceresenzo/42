/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:16:26 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:16:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEOBJECT_HPP_
# define GAMEOBJECT_HPP_

#include <engine/scene/Component.hpp>
#include <engine/scene/Node.hpp>
#include <lang/reference/SharedReference.hpp>
#include <string>
#include <list>
#include <utility>

class Component;

class GameObject :
		public Node
{
	public:
		typedef std::list<std::pair<std::string, SharedReference<Component> > > component_map;

	public:
		component_map components;

	public:
		GameObject();

		virtual
		~GameObject();

	public:
		virtual void
		update(double delta_time);

		virtual void
		render();

		SharedReference<Component>
		add_component(Component &component, const std::string &name = "");

		template<typename T>
			T&
			add_component_as(T &component, const std::string &name = "")
			{
				return (reinterpret_cast<T&>(*add_component(component, name)));
			}
};

#endif /* GAMEOBJECT_HPP_ */
