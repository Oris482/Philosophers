/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:51:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/23 22:21:16 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// static int	_check_full()
// {

// }

static int	_check_dead(t_philo *philos, size_t num_philo, size_t time_to_die)
{
	size_t	philo_idx;
	time_t	after_last_meal;	
	time_t	timestamp;		

	philo_idx = 0;
	while (philo_idx < num_philo)
	{
		usleep(DELAY * 3);
		after_last_meal = get_timestamp(philos[philo_idx].args.last_meal);
		if (after_last_meal >= time_to_die)
		{
			pthread_mutex_lock(&philos[philo_idx].args.simul_info->mutex);
			philos[philo_idx].args.simul_info->finish_flag = FINISH;
			timestamp = get_timestamp(philos[philo_idx].args.simul_info->begin);
			printf("%ld %lu %s\n", timestamp, philo_idx + 1, "dead");
			pthread_mutex_unlock(&philos[philo_idx].args.simul_info->mutex);
			return (FINISH);
		}
		philo_idx++;
	}
	return (CONTINUE);
}

void	moniter_philos(t_philo *philos, t_simul_info *simul_info)
{
	const struct timeval	begin = simul_info->begin;
	const size_t			num_philos = simul_info->option.num_philos;
	const size_t			time_to_die = simul_info->option.time_to_die;

	pthread_mutex_unlock(&simul_info->mutex);
	while (42)
	{
		if (_check_dead(philos, num_philos, time_to_die) == FINISH)
			break ;
	}
}
