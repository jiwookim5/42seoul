/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:17:52 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/08/26 18:48:34 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(void)
{
	write(1, "error\n", 7);
	exit(1);
}

int	file_open(char *argv, int i)
{
	int	infile;
	int	outfile;

	if (i == 1)
	{
		infile = open(argv, O_RDONLY);
		if (infile == -1)
			ft_error();
		return (infile);
	}
	else
	{
		outfile = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			ft_error();
	}
	return (outfile);
}

void	get_pipe(char *cmd, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		get_cmd(cmd, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;

	file_zero(&file);
	if (argc == 5)
	{
		file.infile = file_open(argv[1], 1);
		file.outfile = file_open(argv[4], 2);
		dup2(file.infile, STDIN_FILENO);
		dup2(file.outfile, STDOUT_FILENO);
		if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
		{
			write(2, "argc error\n", 10);
			exit(0);
		}
		get_pipe(argv[2], envp);
		get_cmd(argv[3], envp);
	}
	else
		write(2, "argc error\n", 10);
	return (0);
}
