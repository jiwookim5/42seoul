/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:14 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:20:16 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_run(void *arg)
{
	t_philo	*run;

	run = (t_philo *)arg;
	if (run->info->num_philo == 1)
	{
		gettimeofday(&run->info->philos[0].current_eat, 0);
		pthread_mutex_lock(&run->info->m_fork[run->right_fork]);
		run->info->fork[run->right_fork] = 0;
		voice(FORK, run->info, run);
		usleep(run->info->time_to_die);
		pthread_mutex_unlock(&run->info->m_fork[run->right_fork]);
		return (NULL);
	}
	else if ((run->id) % 2 != 0)
		usleep(100);
	philo_day_running(run);
	return (NULL);
}

int	philo_create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		gettimeofday(&info->start_time, 0);
		if (pthread_create(&info->t_philo[i], 0, philo_run, &info->philos[i]))
			return (RET_ERROR);
		i++;
	}
	return (1);
}

int	philo(t_info *info)
{
	int				gap;
	struct timeval	curr;
	int				ret_monitor;

	if (philo_init(info) == RET_ERROR)
		return (RET_ERROR);
	if (philo_create_thread(info) == RET_ERROR)
		return (RET_ERROR);
	ret_monitor = monitor(info);
	gettimeofday(&curr, NULL);
	gap = time_gap(info->start_time, curr);
	if (ret_monitor == -1)
		printf("== philo eat all. dinning end! ==\n");
	else
		printf("[%d] philo %d died\n", gap, ret_monitor);
	if (philo_collect_all_thread(info) == RET_ERROR)
		return (RET_ERROR);
	return (0);
}
