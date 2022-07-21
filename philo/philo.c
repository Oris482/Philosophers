/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:02:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 11:16:42 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_hello(t_mutex_test *lock_section)
{
	pthread_mutex_lock(&lock_section->mutex);
	printf("hello! %ld\n", lock_section->counter);
	lock_section->counter++;
	pthread_mutex_unlock(&lock_section->mutex);
}

int	main(void)
{
	pthread_t		thread[5];
	void			*exit_status[5];
	t_mutex_test	lock_section;
	int				i;

	pthread_mutex_init(&lock_section.mutex, NULL);
	pthread_mutex_lock(&lock_section.mutex);
	lock_section.counter = 1;
	i = 0;
	while (i < 5)
	{
		pthread_create(&thread[i], NULL, (void *)print_hello, &lock_section);
		usleep(100);
		i++;
	}
	pthread_mutex_unlock(&lock_section.mutex);
	while (i > 0)
	{
		pthread_join(thread[i - 1], &exit_status[i - 1]);
		i--;
	}
	return (0);
}