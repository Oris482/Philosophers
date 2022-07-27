/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:02 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/27 13:51:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	time_to_think(t_philo_args *arg)
{
	if (print_message(arg, "is thinking") == FINISH)
		return (FINISH);
	usleep(DELAY * 2);
	return (SUCCESS);
}

int	time_to_sleep(t_philo_args *arg)
{
	const size_t	time_to_die = arg->simul_info->option.time_to_die;
	const size_t	time_to_sleep = arg->simul_info->option.time_to_sleep;
	struct timeval	time_fall_in_sleep;

	gettimeofday(&time_fall_in_sleep, NULL);
	if (print_message(arg, "is sleeping") == FINISH)
		return (FINISH);
	smart_sleep(time_to_sleep);
	return (SUCCESS);
}

int	try_to_eat(t_philo_args *arg)
{
	const size_t	time_to_eat = arg->simul_info->option.time_to_eat;

	pthread_mutex_lock(&arg->fork[LEFT]->mutex);
	if (print_message(arg, "has taken a fork") == FINISH)
	{
		pthread_mutex_unlock(&arg->fork[LEFT]->mutex);
		return (FINISH);
	}
	pthread_mutex_lock(&arg->fork[RIGHT]->mutex);
	gettimeofday(&arg->last_meal, NULL);
	if (print_message(arg, "is eating") == FINISH)
	{
		pthread_mutex_unlock(&arg->fork[LEFT]->mutex);
		pthread_mutex_unlock(&arg->fork[RIGHT]->mutex);
		return (FINISH);
	}
	smart_sleep(time_to_eat);
	arg->eat_counter++;
	pthread_mutex_unlock(&arg->fork[LEFT]->mutex);
	pthread_mutex_unlock(&arg->fork[RIGHT]->mutex);
	return (SUCCESS);
}

void	*run_philo(void *args)
{
	t_philo_args *const	arg = args;

	pthread_mutex_lock(&arg->simul_info->mutex);
	arg->last_meal = arg->simul_info->begin;
	pthread_mutex_unlock(&arg->simul_info->mutex);
	if (arg->my_num % 2 == 0)
		usleep(DELAY * 4);
	while (42)
	{
		if (try_to_eat(arg) == FINISH)
			return (NULL);
		if (time_to_sleep(arg) == FINISH)
			return (NULL);
		if (time_to_think(arg) == FINISH)
			return (NULL);
	}
	return (NULL);
}
