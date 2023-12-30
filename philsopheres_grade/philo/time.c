/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/16 18:25:47 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_init(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		print_error("Gettimeofday returned\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_pass_time(long int time_to_eat, t_info *info)
{
	long int	start;
	long int	now;

	start = time_init();
	while (!(check_death(info->philo)))
	{
		now = time_init();
		if ((now - start) >= time_to_eat)
			break ;
		usleep(500);
	}
}
