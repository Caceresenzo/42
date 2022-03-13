/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Component.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:16:50 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 01:16:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/scene/Component.hpp>

Component::Component(GameObject &parent, const std::string &name) :
		parent(parent),
		name(name)
{
}

Component::~Component()
{
}

void
Component::update()
{
}

void
Component::render()
{
}

Transform<float>&
Component::transform()
{
	return (parent.transform);
}
