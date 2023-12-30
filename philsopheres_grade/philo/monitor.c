/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/12/30 18:57:18 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&(philo->info->death_m));
	result = 0;
	if (philo->info->death_flag != 0)
		result = philo->info->death_flag;
	pthread_mutex_unlock(&(philo->info->death_m));
	return (result);
}

int	check_time(t_philo philo)
{
	int	result;

	pthread_mutex_lock(&(philo.info->death_m));
	result = philo.info->time_to_die;
	pthread_mutex_unlock(&(philo.info->death_m));
	return (result);
}

int	thread_check_death(t_philo philo)
{
	pthread_mutex_lock(&(philo.eye));
	if (time_init() - philo.thread_time > check_time(philo))
	{
		pthread_mutex_unlock(&(philo.eye));
		return (1);
	}
	pthread_mutex_unlock(&(philo.eye));
	return (0);
}

int	must_eat_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->eat_mutex));
	if (philo->info->must_eat > 0 && philo->info->philo_number == \
		philo->info->finished_eat)
	{
		pthread_mutex_lock(&(philo->info->death_m));
		philo->info->death_flag = 1;
		pthread_mutex_unlock(&(philo->info->death_m));
		pthread_mutex_unlock(&(philo->info->eat_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->eat_mutex));
	return (0);
}

void	ft_philo_check_finish(t_philo *philo)
{
	int			i;

	while (!(check_death(philo)))
	{
		if (must_eat_check(philo))
			break ;
		i = 0;
		while (i < philo->info->philo_number)
		{
			if (thread_check_death(philo[i]))
			{
				printf_time_number(philo, "died");
				pthread_mutex_lock(&(philo->info->death_m));
				philo->info->death_flag = 1;
				pthread_mutex_unlock(&(philo->info->death_m));
				return ;
			}
			i++;
		}
	}
}
