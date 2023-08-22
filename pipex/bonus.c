/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:01:48 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/08/22 17:15:18 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_open(char *argv, int i)
{
	int	infile;
	int	outfile;

	if (i == 1)
	{
		infile = open(argv, O_RDONLY);
		if (infile == -1)
		{
			printf("sdf\n");
			ft_error();
		}
		return (infile);
	}
	else
	{
		outfile = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			ft_error();
		return (outfile);
	}
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
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		get_cmd(cmd, envp);
	}
}

void	file_zero(t_file *file)
{
	file->infile = 0;
	file->outfile = 0;
	file->j = 0;
}

void	handle_args(int argc, char **argv, char **envp, t_file file)
{
	int	i;

	i = 3;
	if (argc >= 5)
	{
		dup2(file.infile, STDIN_FILENO);
		dup2(file.outfile, STDOUT_FILENO);
		if (file.j == 0)
			get_pipe(argv[2], envp);
		while (i < argc - 2)
		{
			get_pipe(argv[i], envp);
			i++;
		}
		get_cmd(argv[i], envp);
	}
	else
		write(1, "argc error\n", 10);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_file	file;

	i = 3;
	file_zero(&file);
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
	{
		here_doc(argc, argv, &file);
		file.j++;
	}
	if (ft_strncmp(argv[1], "here_doc\0", 9) != 0)
		printf("fucksdfasd\n");
	else
	{
		file.infile = file_open(argv[1], 1);
		file.outfile = file_open(argv[argc - 1], 2);
	}
	unlink(".here_doc_tmp");
	handle_args(argc, argv, envp, file);
	close(file.infile);
	close(file.outfile);
	return (0);
}
