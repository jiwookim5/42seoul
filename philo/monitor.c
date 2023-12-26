/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:05:57 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 19:52:45 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_dead(t_info *info, t_philo *run)
{
	struct timeval	curr;

	gettimeofday(&curr, 0);
	if (time_gap(run->current_eat, curr) > info->time_to_die)
	{
		pthread_mutex_lock(&info->m_flag_die);
		info->flag_die = 1;
		pthread_mutex_unlock(&info->m_flag_die);
		voice(DEAD, info, run);
		return (run->id);
	}
	return (-1);
}

int	monitor(t_info *info)
{
	int	i;
	int	count_everyone_eat;
	int	must_eat;

	i = 0;
	must_eat = 0;
	while (1)
	{
		if (check_philo_dead(info, &info->philos[i]) == info->philos[i].id)
			break ;
		pthread_mutex_lock(&(info->m_everyone_eat));
		count_everyone_eat = info->count_everyone_eat;
		pthread_mutex_unlock(&(info->m_everyone_eat));
		if (count_everyone_eat == info->num_philo)
		{
			pthread_mutex_lock(&(info->m_must_eat_all_flag));
			info->must_eat_all_flag = 1;
			must_eat = info->must_eat_all_flag;
			pthread_mutex_unlock(&(info->m_must_eat_all_flag));
		}
		if (must_eat == 1)
			return (-1);
		i = 0;
	}
	return (info->philos[i].id + 1);
}
