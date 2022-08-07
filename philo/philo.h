/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:03:17 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 02:19:13 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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

# define LEFT 0
# define RIGHT 1

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

typedef struct s_simul_info
{
	pthread_mutex_t	mutex;
	t_option		option;
	int				finish_flag;
	size_t			full_count;
	struct timeval	begin;
}	t_simul_info;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	size_t			user_id;
}	t_fork;

typedef struct s_philo_args
{
	pthread_mutex_t		start_flag_mutex;
	size_t				my_num;
	struct timeval		last_meal;
	size_t				eat_counter;
	t_fork				*fork[2];
	t_simul_info		*simul_info;
}	t_philo_args;

typedef struct s_philo
{
	pthread_t		thread_id;
	t_philo_args	args;
	void			*exit_status;
}	t_philo;

int		parse_arguments(int argc, char *argv[], t_option *option);
int		exit_with_msg(int err_code, char *err_msg, \
						t_philo *philos, t_fork *forks);
void	*run_philo(void *args);
time_t	get_timestamp(struct timeval begin);
int		print_message(t_philo_args *arg, char *msg, struct timeval *last_meal);
void	smart_sleep(time_t delay);
void	monitor_philos(t_philo *philos, t_simul_info *simul_info, \
						pthread_mutex_t *start_flag_mutex);
#endif
