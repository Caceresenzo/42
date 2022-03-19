/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReferenceCounter.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:34:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/12 20:34:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/reference/ReferenceCounter.hpp>
#include <stdexcept>

ReferenceCounter::ReferenceCounter() :
		m_shared(0),
		m_weak(0)
{
}

long
ReferenceCounter::get_shared() const
{
	return (m_shared);
}

void
ReferenceCounter::add_shared()
{
	++m_shared;
}

long
ReferenceCounter::release_shared()
{
	if (!m_shared)
		throw std::runtime_error("shared counter is going negative");

	--m_shared;

	return (m_shared);
}

long
ReferenceCounter::get_weak() const
{
	return (m_weak);
}

void
ReferenceCounter::add_weak()
{
	++m_weak;
}

long
ReferenceCounter::release_weak()
{
	if (!m_weak)
		throw std::runtime_error("weak counter is going negative");

	--m_weak;

	return (m_weak);
}

long
ReferenceCounter::get()
{
	return (m_shared + m_weak);
}
