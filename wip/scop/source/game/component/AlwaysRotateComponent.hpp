/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlwaysRotateComponent.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:51:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 18:51:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALWAYSROTATECOMPONENT_HPP_
# define ALWAYSROTATECOMPONENT_HPP_

#include <engine/control/Keyboard.hpp>
#include <engine/math/Transform.hpp>
#include <engine/math/vector.hpp>
#include <engine/scene/Component.hpp>

class AlwaysRotateComponent :
		public Component
{
	public:
		Vector<3, float> speed;

	public:
		AlwaysRotateComponent(GameObject &parent);

		virtual
		~AlwaysRotateComponent();

	public:
		virtual void
		update(double delta_time);
};

#endif /* ALWAYSROTATECOMPONENT_HPP_ */
