/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:11:42 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/06/02 16:10:43 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(char *str)
{
	int		a;
	long	b;
	long	res;
	int		final;

	if(!str_check(str))
		ft_error();
	a = 0;
	b = 1;
	res = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32 || str[a] == 34)
			a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			b *= -1;
		a++;
	}
	while (str[a] >= 48 && str[a] <= 57)
	{
		res *= 10;
		res += str[a] - '0';
		a++;
	}
	final = (int)(res * b);
	if (final > 2147483647 || final < -2147483648)
		ft_error();
	return (final);
}