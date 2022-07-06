/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/06 05:22:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * pipex infile "ls -la" "grep -i something" outfile
 * argv[0] pipex 
 * argv[1] infile 
 * argv[2] ls -la
 */
static char	*find_path(size_t	argv_i)
{
	char	*cmd;
	char	*path;
	size_t	i;

	i = 0;
	data()->full_cmd = ft_split(data()->argv[argv_i], ' ');
	cmd = ft_strjoin("/", data()->full_cmd[0]);
	while (data()->path[i++])
	{
		path = ft_strjoin(data()->path[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	return (NULL);
}

/**
 * example: file1 < ls | grep > something" file2
 * 0 STDIN 
 * 1 STDOUT
 * 2 STDERR
 * 3 file.txt
 */
static void	exec_cmds(char **envp)
{
	size_t	i;
	int32_t	pid;
	int32_t	infile;
	int32_t	outfile;
	int32_t	fd[2];
	char	*path;

	i = 0;
	pipe(fd);
	infile = open(data()->argv[0], O_RDONLY);
	outfile = open(data()->argv[data()->argc - 2], O_RDWR | O_CREAT, 0666);
	// printf("outfile: %s\n", data()->argv[0]);
	dup2(infile, STDIN_FILENO);
	while (i < (size_t)data()->argc - 2) 
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == (size_t)data()->argc - 3)
			{
				printf("test");
				dup2(fd[1], outfile);
			}
			else
			{
				path = find_path(i + 1);
				dup2(fd[1], STDOUT_FILENO);
			}
			ft_putnbr_fd(i, STDERR_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (execve(path, data()->full_cmd, envp) == -1)
				display_error("execv failed");
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	input_handler(argc);
	if (!open(argv[1], O_RDONLY))
		display_error("First input file is wrong");
	init_data(argc, argv, envp);
	exec_cmds(envp);
	return (0);
}
