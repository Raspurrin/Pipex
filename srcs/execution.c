/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/05 22:25:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_path(size_t	argv_i)
{
	char	**full_cmd;
	char	*cmd;
	char	*path;
	size_t	i;

	i = 0;
	full_cmd = ft_split(data()->argv[argv_i], ' ');
	cmd = ft_strjoin("/", full_cmd[0]);
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
	size_t	j;
	int32_t	pid;
	int32_t	infile;
	int32_t	fd[2];
	char	*path;

	i = 2;
	j = 1;
	pipe(fd);
	infile = open(data()->argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	while (i < (size_t)data()->argc - 2)
	{
		path = find_path(i);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[j], j);
			execve(data()->path[i - 2], &data()->path[i - 2], envp);
			j--;
		}
		dup2(fd[j], j);
		j++;
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













// why malloc doesn't need typecast first 