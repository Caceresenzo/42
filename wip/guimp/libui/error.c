/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:10:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 19:10:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_ui_error
ui_error_present(const char *message)
{
	t_ui_error error;

	error.present = true;
	error.message = message;
	return (error);
}

t_ui_error
ui_error_absent(void)
{
	t_ui_error error;

	error.present = false;
	error.message = NULL;
	return (error);
}
