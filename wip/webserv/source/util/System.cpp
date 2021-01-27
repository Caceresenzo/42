/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   System.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:48:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/29 20:48:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <util/System.hpp>

unsigned long
System::currentTimeSeconds(void)
{
	struct timeval val;
	if (::gettimeofday(&val, NULL) == -1)
		return (0);

	return (val.tv_sec);
}
