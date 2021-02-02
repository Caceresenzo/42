/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_http_status.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:33:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/25 23:33:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <io/File.hpp>
#include <tests/test_unit.hpp>
#include <string>

CASE("http-status", "isError")
{
	ASSERT(!HTTPStatus::CONTINUE->isError());
	ASSERT(!HTTPStatus::OK->isError());
	ASSERT(!HTTPStatus::MULTIPLE_CHOICES->isError());
	ASSERT(HTTPStatus::BAD_REQUEST->isError());
	ASSERT(HTTPStatus::INTERNAL_SERVER_ERROR->isError());

	ASSERT(!HTTPStatus::isError(100));
	ASSERT(!HTTPStatus::isError(150));
	ASSERT(!HTTPStatus::isError(200));
	ASSERT(!HTTPStatus::isError(250));
	ASSERT(!HTTPStatus::isError(300));
	ASSERT(!HTTPStatus::isError(350));
	ASSERT(HTTPStatus::isError(400));
	ASSERT(HTTPStatus::isError(450));
	ASSERT(HTTPStatus::isError(500));
	ASSERT(HTTPStatus::isError(550));

	return (0);
}
