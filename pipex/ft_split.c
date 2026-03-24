/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:30:50 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/08/15 12:46:16 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_free_one(char **word, size_t wordnum)
{
	size_t	i;

	i = 0;
	while (i < wordnum)
	{
		free(word[i]);
		i++;
	}
	free(word);
	return (0);
}

size_t	ft_word_count(char const *str, char charset)
{
	size_t	count;
	size_t	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str != charset && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*str == charset)
			flag = 0;
		str++;
	}
	return (count);
}

char	**ft_word_len(char **word, char const *str, char charset)
{
	size_t	count;
	size_t	wordnum;
	size_t	wordcount;

	wordcount = ft_word_count(str, charset);
	wordnum = 0;
	while (*str)
	{
		count = 0;
		while ((*str != charset) && *(str) != '\0')
		{
			count++;
			str++;
		}
		if (count != 0)
		{
			word[wordnum] = (char *)malloc((count + 1) * sizeof(char));
			if (word[wordnum] == 0)
				return (ft_free_one(word, wordnum));
			word[wordnum++][count] = '\0';
		}
		while (*str && *str == charset)
			str++;
	}
	return (word);
}

char	**split(char **word, char const *str, char charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*str && *str == charset)
		str++;
	while (*str)
	{
		j = 0;
		while ((*str != charset) && *(str) != '\0')
		{
			word[i][j] = *str;
			j++;
			str++;
		}
		word[i][j] = '\0';
		while (*str && *str == charset)
			str++;
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**word;
	size_t		word_count;

	j = 0;
	i = 0;
	word_count = ft_word_count(s, c);
	if (word_count == 0)
	{
		word = (char **)malloc(1 * sizeof(char *));
		if (!word)
			return (ft_free_one(word, 0));
		word[0] = 0;
		return (word);
	}
	word = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (word == 0)
		return (ft_free_one(word, 0));
	if (ft_word_len (word, s, c) == 0)
		return (0);
	split(word, s, c);
	word[word_count] = 0;
	return (word);
}
 
 
 

