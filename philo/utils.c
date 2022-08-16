/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:54:37 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/16 16:20:11 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	smart_sleep(time_t delay)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	while (42)
	{
		if (get_timestamp(begin) >= delay)
			return ;
		usleep(DELAY);
	}
}

time_t	get_timestamp(struct timeval begin)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec - begin.tv_sec) * 1000) + \
				((now.tv_usec - begin.tv_usec) / 1000));
}

int	exit_with_msg(int err_code, char *err_msg, t_philo *philos, t_fork *forks)
{
	if (philos != NULL)
		free(philos);
	if (forks != NULL)
		free(forks);
	printf("%s", err_msg);
	return (err_code);
}

int	print_message(t_philo_args *arg, char *msg, struct timeval *last_meal)
{
	time_t	timestamp;

	pthread_mutex_lock(&arg->simul_info->mutex);
	if (arg->simul_info->finish_flag == FINISH)
	{
		pthread_mutex_unlock(&arg->simul_info->mutex);
		return (FINISH);
	}
	if (last_meal != NULL)
		gettimeofday(last_meal, NULL);
	timestamp = get_timestamp(arg->simul_info->begin);
	printf("%ld %lu %s\n", timestamp, arg->my_num, msg);
	pthread_mutex_unlock(&arg->simul_info->mutex);
	return (SUCCESS);
}
