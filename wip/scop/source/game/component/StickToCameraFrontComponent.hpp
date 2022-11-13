/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StickToCameraFrontComponent.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:56:36 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 18:56:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STICKTOCAMERAFRONTCOMPONENT_HPP_
# define STICKTOCAMERAFRONTCOMPONENT_HPP_

#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/scene/Component.hpp>
#include <lang/reference/SharedReference.hpp>

class StickToCameraFrontComponent :
		public Component
{
	public:
		SharedReference<PerspectiveCamera> camera;

	public:
		StickToCameraFrontComponent(GameObject &parent);

		virtual
		~StickToCameraFrontComponent();

	public:
		virtual void
		update(double delta_time);
};

#endif /* STICKTOCAMERAFRONTCOMPONENT_HPP_ */
