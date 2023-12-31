/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:49:38 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/31 13:50:27 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_info *info);
int	init_mutex(t_info *info);

int	init(t_info *info, char **argv, int argc)
{
	info->philo_number = atoi_while(argv[1]);
	info->time_to_die = atoi_while(argv[2]);
	info->time_to_eat = atoi_while(argv[3]);
	info->time_to_sleep = atoi_while(argv[4]);
	info->death_flag = 0;
	info->must_eat = -1;
	info->finished_eat = 0;
	info->start_time = 0;
	if (argc == 6)
		info->must_eat = atoi_while(argv[5]);
	if (info->philo_number <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
		if (info->must_eat <= 0)
			return (1);
	if (init_mutex(info))
		return (1);
	if (init_philo(info))
		return (1);
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->philo_number);
	if (!info->philo)
		return (1);
	while (i < info->philo_number)
	{
		info->philo[i].philo_name = i + 1;
		info->philo[i].fork_left = (i + 1) % info->philo_number;
		info->philo[i].fork_right = i;
		info->philo[i].eat = 0;
		info->philo[i].thread_time = 0;
		info->philo[i].info = info;
		pthread_mutex_init(&info->philo[i].eye, NULL);
		i++;
	}
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->count_eat, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->death_m, NULL);
	pthread_mutex_init(&info->eat_mutex, NULL);
	info->fork_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* info->philo_number);
	if (!(info->fork_m))
		return (1);
	i = 0;
	while (i < info->philo_number)
	{
		if (pthread_mutex_init(&(info->fork_m[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}
