/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:02:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/21 19:51:07 by jaesjeon         ###   ########.fr       */
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

int	make_philos(t_philo *philos, t_fork *forks, t_simul_info *simul_info)
{
	size_t			idx;
	const size_t	num_philos = simul_info->option.num_philos;

	idx = 0;
	while (idx < num_philos)
	{
		philos[idx].args.my_num = idx;
		philos[idx].args.simul_info = simul_info;
		philos[idx].args.fork[LEFT] = &forks[idx];
		philos[idx].args.fork[RIGHT] = &forks[(idx + 1) % num_philos];
		simul_info->dead_flag = pthread_create(&philos[idx].thread_id, NULL, \
			run_philo, &philos[idx].args);
		if (simul_info->dead_flag != SUCCESS)
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

	memset(&simul_info, 0, sizeof(t_simul_info));
	if (parse_arguments(argc, argv, &simul_info.option) == ERROR)
		return (exit_with_msg(ERROR, "Error : arguments\n", NULL, NULL));
	philos = (t_philo *)malloc(sizeof(t_philo) * simul_info.option.num_philos);
	forks = (t_fork *)malloc(sizeof(t_fork) * simul_info.option.num_philos);
	if (philos == NULL || forks == NULL)
		return (exit_with_msg(ERROR, "Error : malloc\n", philos, forks));
	pthread_mutex_init(&simul_info.mutex, NULL);
	pthread_mutex_lock(&simul_info.mutex);
	if (make_philos(philos, forks, &simul_info) == ERROR)
		exit_with_msg(simul_info.dead_flag, "Error : thread_create\n", \
						philos, forks);
	gettimeofday(&simul_info.begin, NULL);
	pthread_mutex_unlock(&simul_info.mutex);
	return (wait_join_threads(philos, forks, &simul_info));
}
