/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:53:12 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 01:51:16 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

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

void	exit_with_msg(int err_code, char *err_msg, \
						void *for_free, t_public_sem *public_sem)
{
	if (for_free != NULL)
		free(for_free);
	if (public_sem)
	{
		close_all_sem(public_sem);
		unlink_all_sem();
	}
	printf("%s", err_msg);
	exit(err_code);
}

void	print_message(t_philo_args *arg, char *msg)
{
	time_t	timestamp;

	sem_wait(arg->public_sem->sem_end);
	timestamp = get_timestamp(arg->begin);
	printf("%ld %lu %s\n", timestamp, arg->my_num, msg);
	sem_post(arg->public_sem->sem_end);
}
