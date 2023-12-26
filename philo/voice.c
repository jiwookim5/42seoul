/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:23 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:19:38 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_voice(t_info *info)
{
	int	die;
	int	eat_all;

	pthread_mutex_lock(&info->m_flag_die);
	die = info->flag_die;
	pthread_mutex_unlock(&info->m_flag_die);
	pthread_mutex_lock(&info->m_must_eat_all_flag);
	eat_all = info->must_eat_all_flag;
	pthread_mutex_unlock(&info->m_must_eat_all_flag);
	if (die || eat_all)
		return (1);
	return (0);
}

void	voice(enum e_state state, t_info *info, t_philo *run)
{
	struct timeval	curr;
	int				gap;

	if (check_voice(info))
		return ;
	gettimeofday(&curr, NULL);
	gap = time_gap(info->start_time, curr);
	pthread_mutex_lock(&info->m_print);
	if (state == FORK)
		printf("[%d] philo %d has taken a fork\n", gap, run->id + 1);
	else if (state == EAT)
		printf("[%d] philo %d is eating\n", gap, run->id + 1);
	else if (state == SLEEP)
		printf("[%d] philo %d is sleeping\n", gap, run->id + 1);
	else if (state == THINK)
		printf("[%d] philo %d is thinking\n", gap, run->id + 1);
	else if (state == DEAD)
		printf("[%d] philo %d died\n", gap, run->id + 1);
	pthread_mutex_unlock(&info->m_print);
	return ;
}
