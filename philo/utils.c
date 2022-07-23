/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:54:37 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/23 22:29:50 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	smart_sleep(size_t delay)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	while (42)
		if (get_timestamp(begin) >= delay)
			return ;
}

time_t	get_timestamp(struct timeval begin)
{
	struct timeval	now;
	time_t			over_sec;
	suseconds_t		over_usec;

	gettimeofday(&now, NULL);
	over_sec = now.tv_sec - begin.tv_sec;
	over_usec = now.tv_usec - begin.tv_usec;
	return ((over_sec * 1000) + (over_usec / 1000));
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

int	print_message(t_philo_args *arg, char *msg)
{
	time_t	timestamp;

	pthread_mutex_lock(&arg->simul_info->mutex);
	if (arg->simul_info->finish_flag == FINISH)
	{
		pthread_mutex_unlock(&arg->simul_info->mutex);
		return (FINISH);
	}
	timestamp = get_timestamp(arg->simul_info->begin);
	printf("%ld %lu %s\n", timestamp, arg->my_num, msg);
	pthread_mutex_unlock(&arg->simul_info->mutex);
	return (SUCCESS);
}
