/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:52:16 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/07/29 17:29:42 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_free_a(char **add)
{
	free(*add);
	*add = 0;
	return (0);
}

char	*ft_save(char *add)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!ft_strchr(add, '\n'))
		return (ft_free_a(&add));
	if (add[0] == 0)
		return (0);
	while (add[i] != '\0' && add[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (ft_strlen(add) - i) + 1);
	if (s == 0)
		return (ft_free_a(&add));
	i++;
	while (add[i])
		s[j++] = add[i++];
	s[j] = '\0';
	ft_free_a(&add);
	return (s);
}

char	*ft_extract(char *add)
{
	int		i;
	char	*result;

	i = 0;
	while (add[i] != '\n' && add[i] != '\0')
		i++;
	if (add[i] == '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == 0)
		return (0);
	i = 0;
	while (add[i] != '\0')
	{
		result[i] = add[i];
		if (add[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_add(int fd, char *buff, char *add)
{
	int		byte;
	char	*temp;

	if (add == 0)
		add = ft_strdup("");
	byte = 1;
	while (!ft_strchr(add, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (add == 0)
			add = ft_strdup("");
		if ((byte == -1) || (byte == 0 && add[0] == 0))
		{
			ft_free_a(&add);
			free(buff);
			return (0);
		}
		buff[byte] = '\0';
		temp = add;
		add = ft_strjoin(add, buff);
		free(temp);
	}
	free(buff);
	return (add);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*add;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == 0)
		return (ft_free_a(&add));
	add = ft_add(fd, buff, add);
	if (add == 0)
		return (0);
	line = ft_extract(add);
	if (line == 0)
	{
		ft_free_a(&add);
		return (0);
	}
	add = ft_save(add);
	return (line);
}
