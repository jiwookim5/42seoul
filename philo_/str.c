/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:50:11 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/31 13:50:13 by jiwkim2          ###   ########.fr       */
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
