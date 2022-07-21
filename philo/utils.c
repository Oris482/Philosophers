/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:54:37 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 19:01:45 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

void	print_message(t_philo_args *arg, char *msg)
{
	time_t	timestamp;

	pthread_mutex_lock(&arg->simul_info->mutex);
	timestamp = get_timestamp(arg->simul_info->begin);
	printf("%ld %lu %s\n", timestamp, arg->my_num + 1, msg);
	pthread_mutex_unlock(&arg->simul_info->mutex);
}