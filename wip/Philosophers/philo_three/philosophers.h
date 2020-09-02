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

# define PROGRAM "philo_three"

# define NBR_OF_PARAMETER 5

# define DELAY_WAITING_START 50
# define DELAY_MONITOR 2000
# define DELAY_SLEEP 500

# define SM_GRAB			"grab"
# define SM_STDOUT			"stdout"
# define SM_MILLIS			"millis"
# define SM_FORKS			"forks"
# define SM_DEAD			"dead"
# define SM_STOP			"stop"
# define SM_WAIT_START		"wstart"
# define SM_READY_AWAIT		"rdyaw"
# define SM_STOP_AWAIT		"stpaw"
# define SM_ERROR			"err"
# define SM_EXIT			"ext"
# define SM_MAN_PREFIX		"mn"

char		**g_parameters;
char		**g_man_states;

t_param		g_params;

sem_t		*g_sem_stdout;

sem_t		*g_sem_forks;
sem_t		*g_sem_grab;
sem_t		*g_sem_stop;
sem_t		*g_sem_wait_start;

sem_t		*g_sem_dead;
sem_t		*g_sem_stop_await;

bool		g_stopped;

# define AUTO_HEADER_SECTION

/*
** Automatic header generation:
** - from 29 files
** - found 41 prototypes
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

void		on_stop(void) __attribute__((destructor));

int			ph_main(void);
long		ph_millis(void);
void		ph_runnable(t_man *mn);
void		ph_sem_destroy(sem_t **sem, char *name);
void		ph_sem_destroy_man(sem_t **sem, int index);
sem_t		*ph_sem_open(char *name, int def);
sem_t		*ph_sem_open_man(int index);
int			ph_sim_start(t_table *table);
void		ph_sleep(int millis);
void		ph_table_destroy(t_table *table);
int			ph_table_init(t_table *table);
int			ph_table_init_malloc(t_table *table);
void		ph_update(t_man *man, t_state new_state);

void		phm_destroy(void);
int			phm_init(void);

void		phmm_await(t_table *table, sem_t *sem);
int			phmm_forks(t_table *table);
int			phmm_kill(t_table *table);
void		phmm_run_dead(t_table *table);
void		phmm_shout(t_table *table, sem_t *sem);
int			phmm_start(t_table *table);

void		phms_exit(t_seat *seat);
void		phms_run_starvation(t_seat *seat);
void		phms_run_stop(t_seat *seat);
void		phms_start(t_table *table, int index);
int			phms_start_monitors(t_seat *seat);

# undef AUTO_HEADER_SECTION

#endif
