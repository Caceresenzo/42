/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 01:40:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/03 01:40:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_message
message_from(bool error, const char *text)
{
	t_message message;

	message.error = error;
	message.text = text;
	return (message);
}

t_message
message_simple(const char *text)
{
	return (message_from(false, text));
}

t_message
message_error(const char *text)
{
	return (message_from(true, text));
}

t_message
message_none(void)
{
	return (message_from(false, NULL));
}
