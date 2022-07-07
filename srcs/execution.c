/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/07 04:54:44 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * full_cmd contains 
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
			return (free(cmd), path);
		else
			free(path);
	}
	free(cmd);
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
	infile = open(data()->argv[0], O_RDONLY);
	check_error(infile, "Open failed: ", false);
	outfile = open(data()->argv[data()->argc - 2], O_RDWR | O_CREAT | O_TRUNC, 0666);
	check_error(outfile, "Open failed: ", false);
	check_error(dup2(infile, STDIN_FILENO), "dup2 failed: ", true);
	while (i < (size_t)data()->argc - 3) 
	{
		pipe(fd);
		pid = fork();
		check_error(pid, "fork failed: ", true);
		if (pid == 0)
		{
			path = find_path(i + 1);
			if (i == (size_t)data()->argc - 4)
				check_error(dup2(outfile, STDOUT_FILENO), "dup2 failed: ", true);
			else
				check_error(dup2(fd[1], STDOUT_FILENO), "dup2 failed: ", true);
			close(fd[0]);
			close(fd[1]);
			check_error(execve(path, data()->full_cmd, envp), "execve failed", true);
		}
		waitpid(pid, NULL, 0);
		check_error(dup2(fd[0], STDIN_FILENO), "dup2 failed: ", true);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	close(outfile);
	close(infile);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	input_handler(argc);
	init_data(argc, argv, envp);
	exec_cmds(envp);
	free_at_exit();
	return (0);
}
