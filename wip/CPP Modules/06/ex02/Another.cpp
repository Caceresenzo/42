/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Another.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 12:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Another.hpp"

#include <iostream>

Another::~Another()
{
}

void
Another::hello()
{
	std::cout << "World" << std::endl;
}
