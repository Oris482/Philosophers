/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:51:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/23 21:33:32 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	_check_arguments(t_option *option)
{
	if (option->num_philos == ERRORUL || option->time_to_die == ERRORUL || \
		option->time_to_eat == ERRORUL || option->time_to_sleep == ERRORUL || \
		option->times_must_eat == ERRORUL)
		return (ERROR);
	return (SUCCESS);
}

size_t	ft_strlen(char *arg)
{
	size_t	cnt;

	cnt = 0;
	while (*arg)
	{
		arg++;
		cnt++;
	}
	return (cnt);
}

size_t	ft_atoul(char *arg)
{
	size_t	ret;

	ret = 0;
	if (*arg == '+')
		arg++;
	if (ft_strlen(arg) > 20)
		return (ERRORUL);
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9') || ret > ULMAXHEAD)
			return (ERRORUL);
		if (ret == ULMAXHEAD && *arg >= '5')
			return (ERRORUL);
		ret = ret * 10 + (*arg - '0');
		arg++;
	}
	return (ret);
}

int	parse_arguments(int argc, char *argv[], t_option *option)
{
	if (argc == 5 || argc == 6)
	{
		option->num_philos = ft_atoul(argv[1]);
		option->time_to_die = ft_atoul(argv[2]);
		option->time_to_eat = ft_atoul(argv[3]);
		option->time_to_sleep = ft_atoul(argv[4]);
		if (argc == 6)
		{
			option->times_must_eat = ft_atoul(argv[5]);
			option->times_eat_limited = 1UL;
		}
		if (_check_arguments(option) == SUCCESS)
			return (SUCCESS);
	}
	return (ERROR);
}
