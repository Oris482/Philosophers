/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:51:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/08 16:42:35 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	_check_arguments(t_option *option)
{
	if (option->num_philos == ERRORUL || option->time_to_die == ERRORL || \
		option->time_to_eat == ERRORL || option->time_to_sleep == ERRORL || \
		option->times_must_eat == ERRORUL)
		return (ERROR);
	if (option->limited_eat == 1UL && option->times_must_eat == 0)
		return (ERROR);
	return (SUCCESS);
}

static size_t	_ft_strlen(char *arg)
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

static size_t	_ft_atoul(char *arg)
{
	size_t	ret;

	ret = 0;
	if (*arg == '+')
		arg++;
	if (_ft_strlen(arg) > 20)
		return (ERRORUL);
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9') || ret > ULMAXHEAD)
			return (ERRORUL);
		if (ret == ULMAXHEAD && *arg >= (char)(ULMAXTAIL + '0'))
			return (ERRORUL);
		ret = ret * 10 + (*arg - '0');
		arg++;
	}
	return (ret);
}

static time_t	_ft_atotl(char *arg)
{
	time_t	ret;

	ret = 0;
	if (*arg == '+')
		arg++;
	if (_ft_strlen(arg) > 19)
		return (ERRORL);
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9') || ret > LMAXHEAD)
			return (ERRORL);
		if (ret == ULMAXHEAD && *arg >= (char)(LMAXTAIL + '0'))
			return (ERRORL);
		ret = ret * 10 + (*arg - '0');
		arg++;
	}
	return (ret);
}

int	parse_arguments(int argc, char *argv[], t_option *option)
{
	if (argc == 5 || argc == 6)
	{
		option->num_philos = _ft_atoul(argv[1]);
		option->time_to_die = _ft_atotl(argv[2]);
		option->time_to_eat = _ft_atotl(argv[3]);
		option->time_to_sleep = _ft_atotl(argv[4]);
		if (argc == 6)
		{
			option->times_must_eat = _ft_atoul(argv[5]);
			option->limited_eat = 1UL;
		}
		if (_check_arguments(option) == SUCCESS)
			return (SUCCESS);
	}
	return (ERROR);
}
