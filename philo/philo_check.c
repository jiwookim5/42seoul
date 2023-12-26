/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:02 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:18:09 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	day_running_check_die(int die, t_philo *run)
{
	pthread_mutex_lock(&run->info->m_flag_die);
	die = run->info->flag_die;
	pthread_mutex_unlock(&run->info->m_flag_die);
	return (die);
}

int	day_running_check_eat_all(int eat_all, t_philo *run)
{
	pthread_mutex_lock(&run->m_flag_eat_all);
	eat_all = run->flag_eat_all;
	pthread_mutex_unlock(&run->m_flag_eat_all);
	return (eat_all);
}
