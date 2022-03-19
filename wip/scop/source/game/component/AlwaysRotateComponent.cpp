/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlwaysRotateComponent.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:51:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 18:51:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/component/AlwaysRotateComponent.hpp>

AlwaysRotateComponent::AlwaysRotateComponent(GameObject &parent) :
		Component(parent, "always-rotate")
{
}

AlwaysRotateComponent::~AlwaysRotateComponent()
{
}

void
AlwaysRotateComponent::update(double delta_time)
{
	if (Keyboard::is_pressed(Keyboard::O))
		transform().scaling -= 0.02f;

	if (Keyboard::is_pressed(Keyboard::P))
		transform().scaling += 0.02f;

	transform().rotation += speed * delta_time;
}
