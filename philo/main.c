/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:05:46 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 22:25:20 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_collect_all_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_join(info->t_philo[i], NULL) >= 0)
			i++;
		else
			return (RET_ERROR);
	}
	return (1);
}

void	destroy_info_mutex(t_info *info)
{
	pthread_mutex_destroy(&info->m_everyone_eat);
	pthread_mutex_destroy(&info->m_must_eat_all_flag);
	pthread_mutex_destroy(&info->m_flag_die);
	pthread_mutex_destroy(&info->m_start_time);
	pthread_mutex_destroy(&info->m_print);
	pthread_mutex_destroy(info->m_fork);
}

void	end_philo(t_info *info)
{
	int	i;

	i = 0;
	destroy_info_mutex(info);
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->philos[i].m_current_eat);
		pthread_mutex_destroy(&info->philos[i].m_eat_count);
		pthread_mutex_destroy(&info->philos[i].m_flag_eat_all);
		pthread_mutex_destroy(&(info->m_fork[i]));
		i++;
	}
	free(info->t_philo);
	free(info->m_fork);
	free(info->fork);
	free(info->philos);
	free(info);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = make_info(argc, argv);
	if (!info)
		return (RET_ERROR);
	if (philo(info) == RET_ERROR)
		return (RET_ERROR);
	end_philo(info);
	return (0);
}
