/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:56:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 02:44:51 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static int	_kill_remain_philos(pid_t *pid_list, size_t num_philos)
{
	size_t	idx;
	int		status;

	idx = 0;
	while (idx < num_philos)
	{
		if (!kill(pid_list[idx], SIGKILL))
			waitpid(pid_list[idx], &status, 0);
		idx++;
	}
	return (ERROR);
}

static int	_wait_for_philo(t_option *option, t_public_sem *public_sem, \
					pid_t *pid_list, pthread_t *full_monitor)
{
	const size_t	num_philos = option->num_philos;
	int				status;
	int				exit_code;
	size_t			idx;

	waitpid(-1, &status, 0);
	exit_code = ((status >> 8) & (0x0000ff));
	idx = 0;
	while (idx < num_philos)
	{
		if (!kill(pid_list[idx], SIGKILL))
			waitpid(pid_list[idx], &status, 0);
		idx++;
	}
	while (idx--)
		sem_post(public_sem->sem_full);
	pthread_join(*full_monitor, NULL);
	close_all_sem(public_sem);
	unlink_all_sem();
	return (exit_code);
}

static void	_init_philo_args(size_t	idx, t_philo_args *philo_args)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	philo_args->my_num = idx + 1;
	philo_args->last_meal = now;
	philo_args->begin = now;
	philo_args->eat_counter = 0;
	philo_args->sem_sync = NULL;
}

static int	_fork_philos(pid_t *pid_list, t_philo_args *philo_args)
{
	const size_t	num_philos = philo_args->option->num_philos;
	size_t			idx;

	idx = 0;
	while (idx < num_philos)
	{
		_init_philo_args(idx, philo_args);
		pid_list[idx] = fork();
		if (pid_list[idx] == ERROR)
			return (_kill_remain_philos(pid_list, idx));
		else if (pid_list[idx] == PHILO)
			return (run_philo(philo_args));
		idx++;
	}
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_option		option;
	t_philo_args	philo_args;
	t_public_sem	public_sem;
	pid_t			*pid_list;
	pthread_t		full_monitor;

	if (parse_arguments(argc, argv, &option) == ERROR)
		exit_with_msg(ERROR, "Error: Argument\n", NULL, NULL);
	if (init_all_sem(&public_sem, option.num_philos) == SEM_FAILED)
		exit_with_msg(ERROR, "Error: Semaphore\n", NULL, &public_sem);
	pid_list = (int *)malloc(sizeof(int) * option.num_philos);
	if (pid_list == NULL)
		exit_with_msg(ERROR, "Error: Malloc\n", NULL, &public_sem);
	philo_args.public_sem = &public_sem;
	philo_args.option = &option;
	if (_fork_philos(pid_list, &philo_args) == ERROR)
		exit_with_msg(ERROR, "Error: Fork\n", pid_list, &public_sem);
	if (option.limited_eat)
		if (pthread_create(&full_monitor, NULL, check_philos_full, \
			&(t_monitor_args){&option, &public_sem, pid_list[0]}))
			exit_with_msg(ERROR, "Error: Thread\n", pid_list, &public_sem);
	exit(_wait_for_philo(&option, &public_sem, pid_list, &full_monitor));
	return (0);
}
