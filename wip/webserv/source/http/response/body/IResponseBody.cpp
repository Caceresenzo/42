/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseBody.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:09:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 17:09:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <http/response/body/IResponseBody.hpp>
#include <stddef.h>

IResponseBody::~IResponseBody()
{
}

bool
IResponseBody::isSelfManaged() const
{
	return (false);
}
