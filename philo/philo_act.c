/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:00 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:18:05 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_info *info, t_philo *run)
{
	struct timeval	time;

	voice(EAT, info, run);
	gettimeofday(&time, NULL);
	run->current_eat = time;
	custom_usleep_timer(&time, info->time_to_eat);
	pthread_mutex_lock(&run->m_eat_count);
	run->eat_count++;
	pthread_mutex_unlock(&run->m_eat_count);
	if (run->eat_count == run->info->num_must_eat)
	{
		pthread_mutex_lock(&run->m_flag_eat_all);
		run->flag_eat_all = 1;
		pthread_mutex_unlock(&run->m_flag_eat_all);
	}
}

void	put_down_fork(t_info *info, t_philo *run)
{
	info->fork[run->right_fork] = 1;
	info->fork[run->left_fork] = 1;
	pthread_mutex_unlock(&info->m_fork[run->right_fork]);
	pthread_mutex_unlock(&info->m_fork[run->left_fork]);
}

void	philo_sleep(t_info *info, t_philo *run)
{
	struct timeval	time;

	voice(SLEEP, info, run);
	gettimeofday(&time, NULL);
	custom_usleep_timer(&time, info->time_to_sleep);
}

void	philo_think(t_info *info, t_philo *run)
{
	voice(THINK, info, run);
	usleep(100);
}
