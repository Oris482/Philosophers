/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:02 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 20:21:19 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	time_to_think(t_philo_args *arg)
{
	print_message(arg, "is thinking");
	usleep(DELAY * 2);
	return (SUCCESS);
}

int	time_to_sleep(t_philo_args *arg, struct timeval *last_meal)
{
	const size_t	time_to_die = arg->simul_info->option.time_to_die;
	const size_t	time_to_sleep = arg->simul_info->option.time_to_sleep;
	struct timeval	time_fall_in_sleep;

	gettimeofday(&time_fall_in_sleep, NULL);
	print_message(arg, "is sleeping");
	while (get_timestamp(time_fall_in_sleep) <= time_to_sleep)
	{
		// printf("over = %lu, cut = %lu\n", get_timestamp(*last_meal), time_to_die);
		if (get_timestamp(*last_meal) >= time_to_die)
		{
			printf("over = %lu, cut = %lu\n", get_timestamp(*last_meal), time_to_die);
			print_message(arg, "died");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	try_to_eat(t_philo_args *arg, struct timeval *last_meal)
{
	const size_t	time_to_die = arg->simul_info->option.time_to_die;
	const size_t	time_to_eat = arg->simul_info->option.time_to_eat;
	struct timeval	time_start_to_eat;

	if (get_timestamp(*last_meal) >= time_to_die)
	{
		print_message(arg, "died");
		return (ERROR);
	}
	while (get_timestamp(*last_meal) < time_to_die)
	{
		pthread_mutex_lock(&arg->fork[LEFT]->mutex);
		print_message(arg, "has taken a fork");
		pthread_mutex_lock(&arg->fork[RIGHT]->mutex);
		gettimeofday(&time_start_to_eat, NULL);
		print_message(arg, "is eating");
		gettimeofday(last_meal, NULL);
		while (get_timestamp(time_start_to_eat) <= time_to_eat)
		{
			if (get_timestamp(*last_meal) >= time_to_die)
			{
				print_message(arg, "died");
				return (ERROR);
			}
		}
		break ;
	}
	pthread_mutex_unlock(&arg->fork[LEFT]->mutex);
	pthread_mutex_unlock(&arg->fork[RIGHT]->mutex);
	return (SUCCESS);
}

void	*run_philo(void *args)
{
	t_philo_args *const	arg = args;
	struct timeval		last_meal;				

	pthread_mutex_lock(&arg->simul_info->mutex);
	last_meal = arg->simul_info->begin;
	pthread_mutex_unlock(&arg->simul_info->mutex);
	if (arg->my_num % 2 == 0)
		usleep(DELAY * 3);
	while (1)
	{
		if (try_to_eat(arg, &last_meal) == ERROR)
			return (NULL);
		if (time_to_sleep(arg, &last_meal) == ERROR)
			return (NULL);
	}
	return ;
}