/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowSizeListener.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:17:35 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 20:17:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWSIZELISTENER_HPP_
# define WINDOWSIZELISTENER_HPP_

#include <engine/math/vector.hpp>

class Window;

class WindowSizeListener
{
	public:
		virtual
		~WindowSizeListener();

	public:
		virtual void
		on_size_change(Window &window, const Vector<2, int> &size);
};

#endif /* WINDOWSIZELISTENER_HPP_ */
