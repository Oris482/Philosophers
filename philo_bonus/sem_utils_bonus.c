/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:05:39 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 02:52:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	make_sem_sync_name(char *target_name, size_t suffix)
{
	const char	*base_name = "sem_sync";
	size_t		idx;

	idx = 0;
	while (base_name[idx])
	{
		target_name[idx] = base_name[idx];
		idx++;
	}
	while (suffix)
	{
		target_name[idx] = (suffix % 10) + '0';
		suffix /= 10;
		idx++;
	}
	target_name[idx] = '\0';
}

int	unlink_all_sem(void)
{
	int	ret;

	ret = 0;
	ret |= sem_unlink("sem_start");
	ret |= sem_unlink("sem_forks");
	ret |= sem_unlink("sem_table");
	ret |= sem_unlink("sem_end");
	ret |= sem_unlink("sem_full");
	return (ret);
}

int	close_all_sem(t_public_sem *public_sem)
{
	int	ret;

	ret = 0;
	ret |= sem_close(public_sem->sem_start);
	ret |= sem_close(public_sem->sem_forks);
	ret |= sem_close(public_sem->sem_table);
	ret |= sem_close(public_sem->sem_end);
	ret |= sem_close(public_sem->sem_full);
	return (ret);
}

sem_t	*init_all_sem(t_public_sem *public_sem, size_t num_philos)
{
	unlink_all_sem();
	public_sem->sem_forks = sem_open("sem_start", O_CREAT | O_EXCL, \
									S_IRUSR | S_IWUSR, 0);
	public_sem->sem_forks = sem_open("sem_forks", O_CREAT | O_EXCL, \
									S_IRUSR | S_IWUSR, num_philos);
	public_sem->sem_table = sem_open("sem_table", O_CREAT | O_EXCL, \
									S_IRUSR | S_IWUSR, num_philos / 2);
	public_sem->sem_end = sem_open("sem_end", O_CREAT | O_EXCL, \
									S_IRUSR | S_IWUSR, 1);
	public_sem->sem_full = sem_open("sem_full", O_CREAT | O_EXCL, \
									S_IRUSR | S_IWUSR, 0);
	if (public_sem->sem_forks == SEM_FAILED || \
		public_sem->sem_table == SEM_FAILED || \
		public_sem->sem_end == SEM_FAILED || \
		public_sem->sem_full == SEM_FAILED)
		return (SEM_FAILED);
	else
		return (SUCCESS);
}
