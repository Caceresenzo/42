/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameObject.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:16:26 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:16:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/scene/GameObject.hpp>

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void
GameObject::render()
{
	Node::render();

	for (component_map::iterator iterator = components.begin(); iterator != components.end(); ++iterator)
		iterator->second->render();
}

SharedReference<Component>
GameObject::add_component(Component &component, const std::string &name)
{
	const std::string key = name.empty() ? component.name : name;
	if (key.empty())
		throw IllegalArgumentException("no name specified");

	SharedReference<Component> reference(component);
	components.push_back(std::make_pair(key, reference));

	return (reference);
}
