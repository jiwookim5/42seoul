/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:49:47 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/31 13:50:29 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork_m[philo->fork_left]));
	if (printf_time_philo(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_left]));
		return (1);
	}
	if (philo->info->philo_number == 1)
		return (1);
	pthread_mutex_lock(&(philo->info->fork_m[philo->fork_right]));
	printf_time_philo(philo, "has taken a fork");
	printf_time_philo(philo, "is eating");
	philo->eat++;
	philo->thread_time = time_init();
	ft_pass_time(philo->info->time_to_eat, philo->info);
	pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_right]));
	pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_left]));
	return (0);
}

int	must_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->eat_mutex));
	if (philo->info->must_eat == philo->eat)
	{
		philo->info->finished_eat++;
		pthread_mutex_unlock(&(philo->info->eat_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->eat_mutex));
	return (0);
}

void	*philo_run(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (philo->philo_name % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&(philo->info->death_m));
	while (!(philo->info->death_flag))
	{
		pthread_mutex_unlock(&(philo->info->death_m));
		if (philo_eat(philo) == 1)
			return (0);
		if (must_eat_count(philo) == 1)
			break ;
		printf_time_philo(philo, "is sleeping");
		ft_pass_time(philo->info->time_to_sleep, philo->info);
		printf_time_philo(philo, "is thinking");
		pthread_mutex_lock(&(philo->info->death_m));
	}
	if (philo->info->must_eat != philo->eat)
		pthread_mutex_unlock(&(philo->info->death_m));
	return ((void *)0);
}

int	ft_philo_start(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = time_init();
	while (i < info->philo_number)
	{
		info->philo[i].thread_time = time_init();
		pthread_create(&(info->philo[i].thread), NULL, \
			philo_run, &(info->philo[i]));
		i++;
	}
	ft_philo_check_finish(info->philo);
	i = 0;
	while (i < info->philo_number)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc >= 5 && argc <= 6))
	{
		print_error("Wrong argc\n");
		return (1);
	}
	if (init(&info, argv, argc))
	{
		print_error("Wrong argv\n");
		return (1);
	}
	ft_philo_start(&info);
	free_philo(&info);
}
