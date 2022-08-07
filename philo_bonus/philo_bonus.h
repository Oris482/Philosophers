/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:53:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 02:50:58 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>     //printf
# include <string.h>    //memset
# include <stdlib.h>    //malloc, free
# include <unistd.h>    //write, usleep
# include <sys/time.h>  //gettimeofday
# include <pthread.h>	//pthread
# include <semaphore.h> //sem
# include <signal.h>	//signal

# define ERROR -1
# define SUCCESS 0
# define ERRORUL -1UL
# define ERRORL -1L

# define CONTINUE 0
# define FINISH 1

# define ULMAX 18446744073709551615UL
# define ULMAXHEAD 1844674407370955161UL
# define ULMAXTAIL 5UL

# define LMAX 9223372036854775807L
# define LMAXHEAD 922337203685477580L
# define LMAXTAIL 7L

# define NOTSPECIFIED 0

# define PHILO 0

# define DELAY 500L

typedef struct s_option
{
	size_t	num_philos;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	size_t	limited_eat;
	size_t	times_must_eat;
}	t_option;

typedef struct s_public_sem
{
	sem_t	*sem_forks;
	sem_t	*sem_table;
	sem_t	*sem_end;
	sem_t	*sem_full;
}	t_public_sem;

typedef struct s_philo_args
{
	t_option			*option;
	size_t				my_num;
	struct timeval		last_meal;
	struct timeval		begin;
	size_t				eat_counter;
	sem_t				*sem_sync;
	t_public_sem		*public_sem;
}	t_philo_args;

typedef struct s_monitor_args
{
	t_option		*option;
	t_public_sem	*public_sem;
	pid_t			target_pid;
}	t_monitor_args;

int		parse_arguments(int argc, char *argv[], t_option *option);
void	exit_with_msg(int err_code, char *err_msg, \
						void *for_free, t_public_sem *public_sem);
int		unlink_all_sem(void);
int		close_all_sem(t_public_sem *public_sem);
sem_t	*init_all_sem(t_public_sem *public_sem, size_t num_philos);
int		run_philo(t_philo_args *arg);
time_t	get_timestamp(struct timeval begin);
void	make_sem_sync_name(char *target_name, size_t suffix);
void	print_message(t_philo_args *arg, char *msg);
void	smart_sleep(time_t delay);
void	*check_philo_die(void *philo_args);
void	*check_philos_full(void *monitor_args);
#endif
