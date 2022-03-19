/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   System.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:36:12 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 19:36:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/System.hpp>
#include <sys/time.h>

long long
System::current_time_millis()
{
	struct timeval val = { 0, 0 };
	gettimeofday(&val, NULL);

	return (val.tv_sec * 1000LL + val.tv_usec / 1000);
}
