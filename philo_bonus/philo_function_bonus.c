/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:34:51 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 16:43:37 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static void	_time_to_think(t_philo_args *arg)
{
	print_message(arg, "is thinking");
	usleep(DELAY);
}

static void	_time_to_sleep(t_philo_args *arg)
{
	const time_t	time_to_sleep = arg->option->time_to_sleep;

	print_message(arg, "is sleeping");
	smart_sleep(time_to_sleep);
}

static void	_try_to_eat(t_philo_args *arg)
{
	const time_t	time_to_eat = arg->option->time_to_eat;

	sem_wait(arg->public_sem->sem_table);
	sem_wait(arg->public_sem->sem_forks);
	print_message(arg, "has taken a fork");
	sem_wait(arg->public_sem->sem_forks);
	sem_wait(arg->sem_sync);
	gettimeofday(&arg->last_meal, NULL);
	sem_post(arg->sem_sync);
	print_message(arg, "is eating");
	smart_sleep(time_to_eat);
	sem_wait(arg->sem_sync);
	arg->eat_counter++;
	if (arg->eat_counter == arg->option->times_must_eat)
		sem_post(arg->public_sem->sem_full);
	sem_post(arg->sem_sync);
	sem_post(arg->public_sem->sem_forks);
	sem_post(arg->public_sem->sem_forks);
	sem_post(arg->public_sem->sem_table);
}

int	run_philo(t_philo_args *arg)
{
	char		sem_sync[15];
	pthread_t	time_monitor;

	make_sem_sync_name(sem_sync, arg->my_num);
	sem_unlink(sem_sync);
	arg->sem_sync = sem_open(sem_sync, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	sem_wait(arg->public_sem->sem_start);
	if (arg->sem_sync == SEM_FAILED)
		return (ERROR);
	if (pthread_create(&time_monitor, NULL, check_philo_die, arg))
		return (ERROR);
	while (42)
	{
		_try_to_eat(arg);
		_time_to_sleep(arg);
		_time_to_think(arg);
	}
	return (0);
}
