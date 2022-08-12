/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:02:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/02 20:36:36 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	wait_join_threads(t_philo *philos, t_fork *forks, t_simul_info *simul_info)
{
	size_t	idx;

	idx = 0;
	while (idx < simul_info->option.num_philos)
	{
		pthread_join(philos[idx].thread_id, &philos[idx].exit_status);
		pthread_mutex_destroy(&forks[idx].mutex);
		idx++;
	}
	pthread_mutex_destroy(&simul_info->mutex);
	return (SUCCESS);
}

int	make_philos(t_philo *philos, t_fork *forks, t_simul_info *simul_info, \
				pthread_mutex_t *start_flag_mutex)
{
	size_t			idx;
	const size_t	num_philos = simul_info->option.num_philos;

	idx = 0;
	while (idx < num_philos)
	{
		philos[idx].args.my_num = idx + 1;
		philos[idx].args.simul_info = simul_info;
		simul_info->finish_flag |= pthread_mutex_init(&forks[idx].mutex, NULL);
		philos[idx].args.fork[LEFT] = &forks[idx];
		philos[idx].args.fork[RIGHT] = &forks[(idx + 1) % num_philos];
		simul_info->finish_flag |= \
			pthread_mutex_init(&start_flag_mutex[idx], NULL);
		philos[idx].args.start_flag_mutex = start_flag_mutex[idx];
		pthread_mutex_lock(&start_flag_mutex[idx]);
		simul_info->finish_flag |= pthread_create(&philos[idx].thread_id, NULL, \
			run_philo, &philos[idx].args);
		if (simul_info->finish_flag != SUCCESS)
			return (ERROR);
		idx++;
	}
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_fork			*forks;
	t_simul_info	simul_info;
	pthread_mutex_t	*start_flag_mutex;

	memset(&simul_info, 0, sizeof(t_simul_info));
	if (parse_arguments(argc, argv, &simul_info.option) == ERROR)
		return (exit_with_msg(ERROR, "Error : arguments\n", NULL, NULL));
	if (simul_info.option.num_philos < 2)
		return (exit_with_msg(ERROR, \
				"Error : At least two of philosophers\n", NULL, NULL));
	philos = (t_philo *)malloc(sizeof(t_philo) * simul_info.option.num_philos);
	forks = (t_fork *)malloc(sizeof(t_fork) * simul_info.option.num_philos);
	start_flag_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
						* simul_info.option.num_philos);
	if (philos == NULL || forks == NULL)
		return (exit_with_msg(ERROR, "Error : malloc\n", philos, forks));
	if (pthread_mutex_init(&simul_info.mutex, NULL) != SUCCESS)
		exit_with_msg(ERROR, "Error: Mutex init\n", philos, forks);
	pthread_mutex_lock(&simul_info.mutex);
	if (make_philos(philos, forks, &simul_info, start_flag_mutex) == ERROR)
		exit_with_msg(simul_info.finish_flag, "Error : thread_create\n", \
						philos, forks);
	monitor_philos(philos, &simul_info, start_flag_mutex);
	return (wait_join_threads(philos, forks, &simul_info));
}
