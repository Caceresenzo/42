/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilterChain.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:46:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:31:36 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/after/ErrorFilter.hpp>
#include <http/filter/impl/after/FinalFilter.hpp>
#include <http/filter/impl/after/HeadFilter.hpp>
#include <http/filter/impl/before/AuthenticationFilter.hpp>
#include <http/filter/impl/before/IndexFilter.hpp>
#include <http/filter/impl/before/LocationFilter.hpp>
#include <http/filter/impl/before/MethodFilter.hpp>
#include <http/filter/impl/before/ServerFilter.hpp>
#include <http/filter/impl/between/CGIFilter.hpp>
#include <http/filter/impl/between/MethodHandlingFilter.hpp>
#include <util/Singleton.hpp>

#ifdef HTTP_DEBUG_FILTERCHAIN
#include <io/Socket.hpp>
#include <http/HTTPClient.hpp>
#include <iostream>
#include <typeinfo>
#endif

FilterChain::FilterChain(HTTPClient &client, HTTPRequest &request, HTTPResponse &response) :
		m_client(client),
		m_request(request),
		m_response(response),
		m_current(),
		m_beforePassed(false)
{
}

FilterChain::~FilterChain()
{
}

void
FilterChain::next()
{
	if (!m_current.empty())
	{
		Filter *filter = m_current.front();
		m_current.pop_front();

#ifdef HTTP_DEBUG_FILTERCHAIN
		std::cout << m_client.socket().raw() << ": FilterChain::next()= " << typeid(*filter).name() << std::endl;
#endif

		filter->doFilter(m_client, m_request, m_response, *this);
	}
}

void
FilterChain::doChainingOf(State state)
{
	nextState(state);
	next();
}

bool
FilterChain::nextState(State state)
{
	m_current.clear();

	switch (state)
	{
		case S_BEFORE:
		{
			m_current.push_back(&ServerFilter::instance());
			m_current.push_back(&LocationFilter::instance());
			m_current.push_back(&MethodFilter::instance());
			m_current.push_back(&AuthenticationFilter::instance());
			m_current.push_back(&IndexFilter::instance());

			break;
		}

		case S_BETWEEN:
		{
			m_current.push_back(&CGIFilter::instance());
			m_current.push_back(&MethodHandlingFilter::instance());

			m_current.push_back(&ErrorFilter::instance()); /* Same as S_AFTER. */
			m_current.push_back(&HeadFilter::instance());
			m_current.push_back(&FinalFilter::instance());

			break;
		}

		case S_AFTER:
		{
			m_current.push_back(&ErrorFilter::instance());
			m_current.push_back(&HeadFilter::instance());
			m_current.push_back(&FinalFilter::instance());

			break;
		}

		default:
			return (false);
	}

	return (true);
}
