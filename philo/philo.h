/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:03:17 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 19:48:14 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>     //printf
# include <string.h>    //memset
# include <stdlib.h>    //malloc, free
# include <unistd.h>    //write, usleep
# include <sys/time.h>  //gettimeofday
# include <pthread.h>   //pthread function

# define ERROR -1
# define SUCCESS 0
# define ERRORUL -1UL

# define ULMAX 18446744073709551615UL
# define ULMAXHEAD 1844674407370955161UL
# define ULMAXTAIL 5UL

# define NOTSPECIFIED 0

# define LEFT 0
# define RIGHT 1

# define DELAY 500

typedef struct mutex_test
{
	pthread_mutex_t	mutex;
	size_t			counter;
}	t_mutex_test;

typedef struct s_option
{
	size_t	num_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_eat_limited;
	size_t	times_must_eat;
}	t_option;

typedef struct s_simul_info
{
	pthread_mutex_t	mutex;
	t_option		option;
	int				dead_flag;
	struct timeval	begin;
}	t_simul_info;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	size_t			user_id;
}	t_fork;

typedef struct s_philo_args
{
	size_t				my_num;
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
void	print_message(t_philo_args *arg, char *msg);

#endif
