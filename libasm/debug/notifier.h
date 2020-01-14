/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifier.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:26:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/17 16:26:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTIFIER_H
# define NOTIFIER_H

# include "../tests/tests.h"

# ifndef NOTIFY
#  define NOTIFY 1
# endif

void		notify(char c);
void		notifyi(int i);
void		notifyp(void *p);
void		notifyl(long l);
void		notifys(char *str);
void		notifyempty(void);

#endif
