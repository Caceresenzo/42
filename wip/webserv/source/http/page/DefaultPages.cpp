/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefualtPage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 19:54:36 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/24 19:54:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/page/DefaultPages.hpp>
#include <os/detect_platform.h>
#include <util/Convert.hpp>
#include <webserv.hpp>
#include <utility>

DefaultPages::DefaultPages() :
		m_cache()
{
}

DefaultPages::~DefaultPages()
{
}

const std::string&
DefaultPages::resolve(const HTTPStatus &httpStatus)
{
	iterator it = m_cache.find(httpStatus.code());

	if (it == m_cache.end())
	{
		std::string line = Convert::toString(httpStatus.code()) + " " + httpStatus.reasonPhrase();

		std::string html = ""
				"<html>\n"
				"	<head>\n"
				"		<title>" + line + "</title>\n"
				"	</head>\n"
				"	<body bgcolor=\"white\">\n"
				"		<center>\n"
				"			<h1>" + line + "</h1>\n"
				"		</center>\n"
				"		<hr>\n"
				"		<center>" APPLICATION_NAME_AND_VERSION " (" PLATFORM_NAME ")</center>\n"
		"	</body>\n" /* <- Strange eclipse formatting bug */
		"</html>\n";

		it = m_cache.insert(m_cache.end(), std::make_pair(httpStatus.code(), html));
	}

	return (it->second);
}
