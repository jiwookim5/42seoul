static char	*ft_save(char *add, char *line, int *flag)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!ft_strchr(add, '\n'))
	{
		free(add);
		add = 0;
		return (add);
	}
	if (add[0] == 0)
		return (0);
	while (add[i] != '\0' && add[i] != '\n')
		i++;
	if (add[i] == 0)
	{
		free(add);
	 	return (0);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(add) - i) + 2);
	if (!ft_strchr(add, '\n'))
	{
		free(s);
		return (0);
	}
	if (s == 0)
	{
		*flag = 1;
		free(line);
		free(add);
		add = 0;
		return (0);
	}
	i++;
	while (add[i])
		s[j++] = add[i++];
	s[j] = '\0';
	free(add);
	return (s);
}

static char	*ft_extract(char *add)
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

static char	*ft_add(int fd, char *buff, char *add)
{
	int		byte;
	char	*temp;

	if (add == 0)
		add = ft_strdup("");
	if (add == 0)
	{
		free(buff);
		return (0);
	}
	byte = 1;
	while (!ft_strchr(add, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == 0 && add[0] == '\0')
		{
			free(add);
			add = 0;
			free(buff);
			return (0);
		}
		if (add == 0)
			add = ft_strdup("");
		if (add == NULL)
		{
			free(buff);
			return (0);
		}
		if ((byte == -1) || (byte == 0 && add[0] == 0))
		{
			free(add);
			add = 0;
			free(buff);
			return (0);
		}
		buff[byte] = '\0';
		temp = add;
		add = ft_strjoin(add, buff);
		free(temp);
		if (add == 0)
		{
			free(buff);
			return (0);
		}
	}
	free(buff);
	return (add);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*add;
	char		*line;
	int			flag;

	flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == 0)
		return (0);
	add = ft_add(fd, buff, add);
	if (add == 0)
		return (0);
	line = ft_extract(add);
	if (line == 0)
	{
		free(add);
		add = 0;
		return (0);
	}
	add = ft_save(add, line, &flag);
	if (flag == 1)
		return (0);
	return (line);
}