/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:02:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/20 22:17:39 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_hello(int *i)
{
	printf("hello! %d\n", *i);
}

int	main(void)
{
	pthread_t	thread;
	int	i = 5;

	while (i)
	{
		pthread_create(&thread, NULL, (void *)print_hello, &i);
		usleep(100);
		i--;
	}
	return (0);
}