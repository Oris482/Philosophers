/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:35:03 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 02:42:09 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	*check_philos_full(void *monitor_args)
{
	const t_monitor_args	*arg = monitor_args;
	const size_t			num_philos = arg->option->num_philos;
	size_t					idx;

	idx = 0;
	while (idx < num_philos)
	{
		sem_wait(arg->public_sem->sem_full);
		idx++;
	}
	kill(arg->target_pid, SIGTERM);
	return (NULL);
}

void	*check_philo_die(void *philo_args)
{
	const t_philo_args	*arg = philo_args;
	const time_t		time_to_die = arg->option->time_to_die;
	time_t				after_last_meal;
	time_t				timestamp;

	while (42)
	{
		sem_wait(arg->sem_sync);
		after_last_meal = get_timestamp(arg->last_meal);
		if (after_last_meal >= time_to_die)
		{
			sem_wait(arg->public_sem->sem_end);
			timestamp = get_timestamp(arg->begin);
			printf("%ld %lu %s\n", timestamp, arg->my_num, "died");
			exit(0);
		}
		sem_post(arg->sem_sync);
		usleep(DELAY);
	}
	return (NULL);
}
