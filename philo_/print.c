/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:50:15 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/31 13:50:17 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *tmp)
{
	write(2, tmp, str_length(tmp));
	return ;
}

int	printf_time_philo(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->info->print));
	if (check_death(philo))
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (1);
	}
	printf("%ld %d %s\n", time_init() - philo->info->start_time, \
		philo->philo_name, msg);
	pthread_mutex_unlock(&(philo->info->print));
	return (0);
}

void	free_philo(t_info *info)
{
	free((info->philo));
	free(info->fork_m);
}
