/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:26:56 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/17 16:26:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notifier.h"

int		g_notified_count[5] = { 0, 0, 0, 0, 0 };

void
	notify(char c)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified CHAR    %50c\t(%15d) #%d\n", c, c,
			g_notified_count[0]++);
	fflush(stdout);
}

void
	notifys(char *str)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified STRING  %50s\t(%15p) #%d\n", str, str,
			g_notified_count[1]++);
	fflush(stdout);
}

void
	notifyi(int i)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified INT     %50d\t(%#15x) #%d\n", i, i,
			g_notified_count[2]++);
	fflush(stdout);
}

void
	notifyl(long l)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified LONG    %50ld\t(%#15lx) #%d\n", l, l,
			g_notified_count[3]++);
	fflush(stdout);
}

void
	notifyp(void *p)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified PTR     %50p\t(%15p) #%d\n", p, p,
			g_notified_count[4]++);
	fflush(stdout);
}
