/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2023/03/04 23:48:01 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * Full_cmd contains the cmd with all its flags in seperate elements: "ls -la"
 * It is included in my data struct because it is later used in execve!
 * Cmd takes the first element and joins it with '/': "/ls"
 * Path combines the path with cmd: "usr/bin/ls" and checks its accessibility.
 */
static char	*find_path(t_data *data, size_t	argv_i)
{
	size_t	i;
	char	*cmd;
	char	*path;

	i = 0;
	data->full_cmd = ft_split(data->argv[argv_i], ' ');
	cmd = ft_strjoin("/", data->full_cmd[0]);
	while (data->path[i++])
	{
		path = ft_strjoin(data->path[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), path);
		else
			free(path);
	}
	free(cmd);
	return (display_error(data, "path failed", true), NULL);
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last itteration, the output is redirected to a file. 
 */
void	child_cmd(t_data *data, size_t i, char **envp, int32_t fd[2])
{
	char	*path;

	path = find_path(data, i + 2);
	if (i == (size_t)data->argc - 4)
		dup2(data->outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (execve(path, data->full_cmd, envp) == -1)
	{
		free(path);
		display_error(data, "execve failed", true);
	}
}

/**
 * Creating new child processes for each command executed, facilitating
 * inter-process communication with pipes and redirecting output and input
 * from the commands to STDIN and STDOUT with dup2, which will then be used
 * by the next command. Closing the fds so the program doesn't wait for input.
 */
void	exec_cmds(t_data *data, char **envp)
{
	size_t	i;
	int32_t	pid;
	int32_t	fd[2];

	i = inout_files(data);
	while (i < (size_t)data->argc - 3)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error(data, "fork failed", true);
		if (pid == 0)
			child_cmd(data, i, envp, fd);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	close(data->outfile);
	close(data->infile);
}
