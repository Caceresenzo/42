/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:12:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 22:12:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optional.h"

t_optional_int
optional_int(int value)
{
	t_optional_int optional;

	optional.present = true;
	optional.value = value;
	return (optional);
}

int
optional_int_or_else(t_optional_int optional, int default_value)
{
	if (optional.present)
		return (optional.value);
	return (default_value);
}
