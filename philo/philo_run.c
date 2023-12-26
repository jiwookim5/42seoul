/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:10 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:21:19 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_info *info, t_philo *run)
{
	if (run->id % 2)
	{
		pthread_mutex_lock(&info->m_fork[run->left_fork]);
		info->fork[run->left_fork] = 0;
		voice(FORK, info, run);
		pthread_mutex_lock(&info->m_fork[run->right_fork]);
		info->fork[run->right_fork] = 0;
		voice(FORK, info, run);
	}
	else
	{
		pthread_mutex_lock(&info->m_fork[run->right_fork]);
		info->fork[run->right_fork] = 0;
		voice(FORK, info, run);
		pthread_mutex_lock(&info->m_fork[run->left_fork]);
		info->fork[run->left_fork] = 0;
		voice(FORK, info, run);
	}
}

void	philo_day_running(t_philo *run)
{
	int	die;
	int	eat_all;

	die = 0;
	eat_all = 0;
	while (1)
	{
		die = day_running_check_die(die, run);
		if (die)
			break ;
		grab_fork(run->info, run);
		philo_eat(run->info, run);
		put_down_fork(run->info, run);
		eat_all = day_running_check_eat_all(eat_all, run);
		if (eat_all)
			break ;
		philo_sleep(run->info, run);
		philo_think(run->info, run);
	}
	if (!die)
	{
		pthread_mutex_lock(&run->info->m_everyone_eat);
		run->info->count_everyone_eat++;
		pthread_mutex_unlock(&run->info->m_everyone_eat);
	}
}
