/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowSizeListener.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:17:35 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 20:17:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/listener/WindowSizeListener.hpp>

WindowSizeListener::~WindowSizeListener()
{
}

void
WindowSizeListener::on_size_change(Window&, const Vector<2, int>&)
{
}
