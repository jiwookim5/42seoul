/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:08 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:21:08 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		memset(&info->philos[i], 0, sizeof(t_philo));
		info->philos[i].info = info;
		info->philos[i].eat_count = 0;
		info->philos[i].id = i;
		info->philos[i].right_fork = i;
		info->philos[i].left_fork = (i + 1) % info->num_philo;
		i++;
	}
	return (1);
}

int	init_info_argv(int argc, char *argv[], t_info *info)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	else
		info->num_must_eat = -1;
	if (info->num_philo <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0 || \
		((argc == 6) && info->num_must_eat <= 0))
	{
		p_error("ERROR : invalid input!\n");
		return (RET_ERROR);
	}
	return (1);
}

int	setting_struct(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	info->t_philo = malloc(sizeof(pthread_t) * info->num_philo);
	info->fork = malloc(sizeof(int) * info->num_philo);
	info->m_fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->philos || !info->t_philo || !info->fork || !info->m_fork)
		return (RET_ERROR);
	if (pthread_mutex_init(&(info->m_everyone_eat), 0) || \
		pthread_mutex_init(&(info->m_flag_die), 0) || \
		pthread_mutex_init(&(info->m_start_time), 0) || \
		pthread_mutex_init(&(info->m_must_eat_all_flag), 0) || \
		pthread_mutex_init(&(info->m_print), 0))
		return (RET_ERROR);
	return (1);
}

int	check_argv(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->fork[i] = 1;
		if (pthread_mutex_init(&info->m_fork[i], 0))
		{
			p_error("ERROR : mutex initialize error");
			return (RET_ERROR);
		}
		i++;
	}
	return (1);
}

t_info	*make_info(int argc, char **argv)

{
	t_info	*info;

	if (!(argc == 5 || argc == 6))
		return (0);
	info = (t_info *)malloc(sizeof(t_info));
	memset(info, 0, sizeof(t_info));
	if (init_info_argv(argc, argv, info) == RET_ERROR || \
		setting_struct(info) == RET_ERROR || \
		check_argv(info) == RET_ERROR)
		return (0);
	return (info);
}
