/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objects.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:18:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:18:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Objects.hpp"

Objects::Objects()
{
}

Objects::~Objects()
{
}

Objects::Objects(const Objects &other)
{
	(void)other;
}

Objects&
Objects::operator=(const Objects &other)
{
	(void)other;

	return (*this);
}
