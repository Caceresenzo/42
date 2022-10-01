/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:10:31 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 19:10:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>
# include <string.h>

typedef struct s_error
{
	bool present;
	const char *message;
} t_ui_error;

t_ui_error
ui_error_present(const char *message);

t_ui_error
ui_error_absent(void);

#endif
