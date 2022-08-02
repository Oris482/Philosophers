/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:51:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/02 20:30:27 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	_check_full(t_philo *philos, size_t num_philo, \
							size_t times_must_eat)
{
	size_t	idx;
	time_t	timestamp;

	idx = 0;
	while (idx < num_philo)
	{
		if (philos[idx].args.eat_counter < times_must_eat)
			break ;
		if (idx != num_philo - 1)
		{
			idx++;
			continue ;
		}
		pthread_mutex_lock(&philos[idx].args.simul_info->mutex);
		philos[idx].args.simul_info->finish_flag = FINISH;
		timestamp = get_timestamp(philos[idx].args.simul_info->begin);
		printf("%ld %s\n", timestamp, "Everybody full");
		pthread_mutex_unlock(&philos[idx].args.simul_info->mutex);
		return (FINISH);
	}
	return (CONTINUE);
}

static int	_check_dead(t_philo *philos, size_t num_philo, time_t time_to_die)
{
	size_t	idx;
	time_t	after_last_meal;	
	time_t	timestamp;

	idx = 0;
	while (idx < num_philo)
	{					
		after_last_meal = get_timestamp(philos[idx].args.last_meal);
		if (after_last_meal >= time_to_die)
		{
			pthread_mutex_lock(&philos[idx].args.simul_info->mutex);
			philos[idx].args.simul_info->finish_flag = FINISH;
			timestamp = get_timestamp(philos[idx].args.simul_info->begin);
			printf("%ld %lu %s\n", timestamp, idx + 1, "died");
			pthread_mutex_unlock(&philos[idx].args.simul_info->mutex);
			return (FINISH);
		}
		idx++;
	}
	return (CONTINUE);
}

static void	_initialize_begin_time(t_philo *philos, const size_t num_philos, \
									t_simul_info *simul_info)
{
	struct timeval	now;
	size_t			idx;

	idx = 0;
	gettimeofday(&now, NULL);
	simul_info->begin = now;
	while (idx < num_philos)
	{
		philos[idx].args.last_meal = now;
		idx++;
	}
}

void	monitor_philos(t_philo *philos, t_simul_info *simul_info, \
						pthread_mutex_t *start_flag_mutex)
{
	const size_t			num_philos = simul_info->option.num_philos;
	const time_t			time_to_die = simul_info->option.time_to_die;
	const size_t			limited_eat = simul_info->option.limited_eat;
	const size_t			times_must_eat = simul_info->option.times_must_eat;
	size_t					idx;

	idx = 0;
	_initialize_begin_time(philos, num_philos, simul_info);
	pthread_mutex_unlock(&simul_info->mutex);
	while (idx < num_philos)
	{
		pthread_mutex_unlock(&philos[idx].args.start_flag_mutex);
		pthread_mutex_destroy(&(philos[idx].args.start_flag_mutex));
		idx++;
	}
	free(start_flag_mutex);
	smart_sleep(time_to_die);
	while (42)
	{
		if ((_check_dead(philos, num_philos, time_to_die) == FINISH) || \
			(limited_eat && _check_full(philos, num_philos, \
										times_must_eat) == FINISH))
			break ;
		usleep(DELAY * 3);
	}
}
