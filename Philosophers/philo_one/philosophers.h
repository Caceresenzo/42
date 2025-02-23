/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:44:38 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:44:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>

# include "philosophers_structs.h"

typedef	void	*(*t_run)(void *);

# define FD_IN 0
# define FD_OUT 1
# define FD_ERR 2

# define PROGRAM "philo_one"

# define NBR_OF_PARAMETER 5

# define DELAY_WAITING_START 50
# define DELAY_MONITOR 2000
# define DELAY_SLEEP 500

# define IS_MALLOC	1
# define IS_MUTEX	2
# define IS_FORK	4
# define IS_THREAD	8
# define IS_MONITOR	16

char		**g_parameters;
char		**g_man_states;

t_param		g_params;

t_mutex		g_mutex_stdout;
t_mutex		g_mutex_millis;

t_mutex		g_mutex_dead;

bool		g_someone_is_dead;

# define AUTO_HEADER_SECTION

/*
** Automatic header generation:
** - from 21 files
** - found 29 prototypes
** - at 13:42:20, the August 25 (2020)
** - with version 1.1
*/

int			err_errno(int err, int child_id);
int			err_must_be_at_least_1_philo(void);
int			err_param_not_int(int param);
int			err_print_usage(void);

int			ft_atoi(char *str, bool *err);
void		*ft_malloc(size_t n);
void		*ft_memset(void *src, int c, size_t n);
void		ft_putstr(char *str);
void		ft_putstr_errno(char *msg);
void		ft_putstr_fd(char *str, int fd);
size_t		ft_sputnbr(char *to, unsigned long nbr);
size_t		ft_sputstr(char *to, char *str);
size_t		ft_strlen(char *str);

int			main(int argc, char **argv);

void		on_stop(void);

int			ph_main(void);
long		ph_millis(void);
void		ph_runnable(t_man *mn);
int			ph_sim_start(t_table *table);
void		ph_sleep(int millis);
void		ph_table_destroy(t_table *table);
int			ph_table_init(t_table *table);
int			ph_table_init_malloc(t_table *table);
void		ph_update(t_man *man, t_state new_state);

void		phm_destroy(void);
int			phm_init(void);
void		phm_join(t_table *table);
void		phm_run_starvation(t_man *man);
int			phm_threads(t_table *table);

# undef AUTO_HEADER_SECTION

#endif
