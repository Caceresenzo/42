/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StickToCameraFrontComponent.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:56:36 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 18:56:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/component/StickToCameraFrontComponent.hpp>

StickToCameraFrontComponent::StickToCameraFrontComponent(GameObject &parent) :
		Component(parent, "stick-to-camera-front")
{
}

StickToCameraFrontComponent::~StickToCameraFrontComponent()
{
}

void
StickToCameraFrontComponent::update(double)
{
	transform().translation = camera->position() + camera->front();
}
