/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:02 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/02 19:40:09 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	time_to_think(t_philo_args *arg)
{
	if (print_message(arg, "is thinking", NULL) == FINISH)
		return (FINISH);
	usleep(DELAY);
	return (SUCCESS);
}

int	time_to_sleep(t_philo_args *arg)
{
	const time_t	time_to_sleep = arg->simul_info->option.time_to_sleep;
	struct timeval	time_fall_in_sleep;

	gettimeofday(&time_fall_in_sleep, NULL);
	if (print_message(arg, "is sleeping", NULL) == FINISH)
		return (FINISH);
	smart_sleep(time_to_sleep);
	return (SUCCESS);
}

int	try_to_eat(t_philo_args *arg)
{
	const time_t	time_to_eat = arg->simul_info->option.time_to_eat;
	const size_t	first_try = arg->my_num % 2 == 0;
	const size_t	second_try = arg->my_num % 2 != 0;

	pthread_mutex_lock(&arg->fork[first_try]->mutex);
	if (print_message(arg, "has taken a fork", NULL) == FINISH)
	{
		pthread_mutex_unlock(&arg->fork[first_try]->mutex);
		return (FINISH);
	}
	pthread_mutex_lock(&arg->fork[second_try]->mutex);
	if (print_message(arg, "is eating", &arg->last_meal) == FINISH)
	{
		pthread_mutex_unlock(&arg->fork[first_try]->mutex);
		pthread_mutex_unlock(&arg->fork[second_try]->mutex);
		return (FINISH);
	}
	// printf("%ld %ld start to sleep\n", get_timestamp(arg->simul_info->begin), arg->my_num);
	smart_sleep(time_to_eat);
	// printf("%ld %ld end sleep\n", get_timestamp(arg->simul_info->begin), arg->my_num);
	arg->eat_counter++;
	pthread_mutex_unlock(&arg->fork[first_try]->mutex);
	pthread_mutex_unlock(&arg->fork[second_try]->mutex);
	return (SUCCESS);
}

void	*run_philo(void *args)
{
	t_philo_args *const	arg = args;

	pthread_mutex_lock(&arg->start_flag_mutex);
	pthread_mutex_unlock(&arg->start_flag_mutex);
	free(&arg->start_flag_mutex);
	if (arg->my_num % 2 == 0)
		usleep(DELAY * 20);
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
