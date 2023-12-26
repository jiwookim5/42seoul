/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:12 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 18:06:13 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	p_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (RET_ERROR);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (ERROR);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 2147483647)
			return (ERROR);
		else
			res = res * 10 + (str[i] - '0');
		if (!res || !str[i])
			break ;
		i++;
	}
	if ((str[i] < '0' || str[i] > '9') && str[i] != 0)
		return (ERROR);
	return ((int) res);
}
