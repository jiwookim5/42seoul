/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:23 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/13 16:52:55 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_length(char *tmp)
{
	int	i;

	if (tmp == (void *)0)
		return (0);
	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

long	atoi_while(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			result = (10 * result) + str[i] - '0';
		else
			print_error("Wrong number\n");
		i++;
	}
	if (i >= 11)
	{
		print_error("Wrong number\n");
		return (-1);
	}
	return (result);
}
