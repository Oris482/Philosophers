/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:56:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/02 21:53:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	main(void)
{
	sem_t	*semaphore;
	int		pid;

	sem_unlink("semaphore");
	semaphore = sem_open("storage", O_CREAT, 0644, 1);
	printf("%p\n", semaphore);
	pid = fork();
	sem_wait(semaphore);
	printf("%d : get lock!\n", pid);
	sem_post(semaphore);
	sem_close(semaphore);
	sem_unlink("semaphore");
	return (0);
}