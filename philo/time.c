/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:20 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 20:06:32 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_gap(struct timeval start_time, struct timeval now_time)
{
	time_t	sec;
	time_t	mili;

	sec = (now_time.tv_sec) - (start_time.tv_sec);
	mili = (sec * 1000) + ((now_time.tv_usec - start_time.tv_usec) / 1000);
	return ((int)mili);
}

void	custom_usleep_timer(struct timeval *start, int sleep_time)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	while (time_gap(*start, now) < sleep_time)
	{
		usleep(300);
		gettimeofday(&now, 0);
	}
}
