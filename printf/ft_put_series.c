/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_series.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:30 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/05/18 17:04:14 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd(char c, int fd)
{
	if (write (fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_putchar_fd(s[i], fd) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_minus(int n, int fd)
{
	n = n * -1;
	if (write(fd, "-", 1) == -1)
		return (-1);
	return (n);
}

int	ft_exception(int n, int fd)
{
	if (n == -2147483648)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return (-1);
		return (0);
	}
	else if (n == 0)
	{
		if (write(fd, "0", 1) == -1)
			return (-1);
		return (0);
	}
	if (n < 0)
	{
		n = ft_minus(n, fd);
		if (n == -1)
			return (-1);
	}
	return (n);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	tmp;
	int		a;

	a = ft_exception(n, fd);
	if (a == -1)
		return (-1);
	if (a == 0)
		return (0);
	if (a < 10)
	{
		tmp = a + 48;
		if (write(fd, &tmp, 1) == -1)
			return (-1);
		return (0);
	}
	else
		if (ft_putnbr_fd (a / 10, fd) == -1)
			return (-1);
	if (ft_putnbr_fd (a % 10, fd) == -1)
		return (-1);
	return (0);
}


char *get_path(char *commend, char **envp) {
	char *path;
	int i;
	char *c;
	char *path_cmd;
	char *result = commend; 

	i = 1;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = envp[i] + 5;
	while (path && ft_str_chr(path, ':') > 0) {
		c = ft_str_dup(path, ft_str_chr(path, ':'));
		path_cmd = path_join(c, commend);
		if (access(path_cmd, X_OK) == 0) {
			result = path_cmd; 
			break; 
		}
		path += ft_str_chr(path, ':') + 1;
		free(path_cmd);
		free(c);
	}
	if (ft_str_chr(path, '\0')) {
		c = ft_str_dup(path, ft_str_chr(path, '\0'));
		path_cmd = path_join(c, commend);
		if (access(path_cmd, X_OK) == 0) {
			result = path_cmd;
		}
		free(path_cmd);
		free(c);
	}
	return result;
}