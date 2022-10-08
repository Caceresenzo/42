/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:30:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 22:30:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_H
# define OPTIONAL_H

# include <stdbool.h>

typedef struct s_optional_int
{
	bool present;
	int value;
} t_optional_int;

typedef t_optional_int t_optional_color;

t_optional_int
optional_int(int value);

int
optional_int_or_else(t_optional_int optional, int default_value);

#endif
