/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:03:17 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 11:06:50 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>     //printf
# include <string.h>    //memset
# include <stdlib.h>    //malloc, free
# include <unistd.h>    //write, usleep
# include <sys/time.h>  //gettimeofday
# include <pthread.h>   //pthread function

typedef struct mutex_test {
	pthread_mutex_t	mutex;
	size_t			counter;
}	t_mutex_test;

#endif