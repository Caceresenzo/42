/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:47:58 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 23:47:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_H
# define OPTIONAL_H

# include <stdbool.h>

typedef struct s_error
{
	bool present;
	const char *message;
} t_error;

#endif
