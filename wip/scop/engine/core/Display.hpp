/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:24:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:24:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

#include <engine/math/vector.hpp>

class Display
{
	private:
		Display();

	public:
		static int
		x();

		static int
		y();

		static int
		width();

		static int
		height();

		static Vector<2, int>
		size();
};

#endif /* DISPLAY_HPP_ */
