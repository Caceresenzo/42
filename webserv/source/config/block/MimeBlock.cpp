/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeBlock.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:23:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/26 00:23:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/MIMEBlock.hpp>
#include <util/helper/DeleteHelper.hpp>

MimeBlock::MimeBlock() :
		m_includes(),
		m_defines()
{
}

MimeBlock::~MimeBlock()
{
	DeleteHelper::pointers<MIME>(m_defines);
}

MimeBlock&
MimeBlock::includes(const std::list<std::string> &includes)
{
	m_includes.set(includes);

	return (*this);
}

MimeBlock&
MimeBlock::defines(const std::list<MIME const*> &defines)
{
	m_defines.set(defines);

	return (*this);
}
