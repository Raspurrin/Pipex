/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/05 18:49:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_path(t_data *data, size_t	argv_i)
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

// why malloc doesn't need typecast first 

// static void	in_file(t_data *data)
// {
	
// }

static void	exec_cmds(t_data *data)
{
	size_t	i;
	int8_t	pid;
	int8_t	fd[2];
	char	*path;

	i = 1;

	pipe(fd);

	while (i < (size_t)data()->argc - 2)
	{
		path = find_path(data, i);
		pid = fork();
		// if (pid == 0)
	}
}

// static void out_file()

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;

	input_handler(argc);
	if (!open(argv[1], O_RDONLY))
		display_error("First input file is wrong");
	data(argc, argv, envp);
	exec_cmds(&data);
	return (0);
}
