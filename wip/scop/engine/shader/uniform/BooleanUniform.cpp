/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BooleanUniform.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:33:30 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:33:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/uniform/BooleanUniform.hpp>

BooleanUniform::BooleanUniform(const std::string &name) :
		Uniform(name)
{
}

void
BooleanUniform::set(bool value)
{
	glUniform1i(location(), value);
}
