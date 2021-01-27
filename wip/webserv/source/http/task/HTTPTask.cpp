/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPTask.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:38:16 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/10 19:38:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/task/HTTPTask.hpp>

HTTPTask::~HTTPTask()
{
}

bool
HTTPTask::timeoutTouch(void)
{
	return (false);
}
