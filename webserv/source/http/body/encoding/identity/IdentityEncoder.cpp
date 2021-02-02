/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IdentityEncoder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:24:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/09 01:24:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/identity/IdentityEncoder.hpp>

IdentityEncoder::IdentityEncoder()
{
}

IdentityEncoder::~IdentityEncoder()
{
}

std::string
IdentityEncoder::encode(const std::string &input)
{
	return (input);
}
