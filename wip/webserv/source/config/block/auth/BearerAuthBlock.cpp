/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BearerAuthBlock.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:16:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 17:16:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/auth/BearerAuthBlock.hpp>
#include <string>

const std::string BearerAuthBlock::TYPE = "bearer";
const std::string BearerAuthBlock::PRETTY_TYPE = "Bearer";

BearerAuthBlock::BearerAuthBlock(const std::string &token) :
		AuthBlock(),
		m_token(token)
{
}

BearerAuthBlock::~BearerAuthBlock()
{
}

bool
BearerAuthBlock::authorize(const std::string &credentials) const
{
	return (m_token == credentials);
}

const std::string&
BearerAuthBlock::type() const
{
	return (TYPE);
}

const std::string&
BearerAuthBlock::prettyType() const
{
	return (PRETTY_TYPE);
}
