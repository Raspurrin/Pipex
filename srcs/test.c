/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/01 05:51:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(int argc, char **argv, t_data *data, char **envp)
{
	size_t	i;

	i = 0;
	data->argc = argc;
	data->argv = malloc((argc) * sizeof(char *));
	while (i++ < (size_t)argc - 1)
		data->argv[i - 1] = ft_substr(argv[i], 0, ft_strlen(argv[i]));
	data->argv[i - 1] = NULL;
	// data->args = malloc(argc - 1 * sizeof(char ***));
	// while (i < (size_t)argc - 1)
	// 	data->args[i] = ft_split(argv[i + 1], ' ');
	while (*envp != NULL)
	{
		if (!ft_strncmp("PATH", *envp, 4))
		{
			data->path = ft_split(*envp, ':');
			data->path[0] = ft_substr(data->path[0], 5, \
							ft_strlen(data->path[0]) - 5);
		}
		envp++;
	}
}

char	*find_path(t_data *data, size_t	argv_i)
{
	char	**full_cmd;
	char	*cmd;
	char	*path;
	size_t	i;

	i = 0;
	full_cmd = ft_split(data->argv[argv_i], ' ');
	cmd = ft_strjoin("/", full_cmd[0]);
	while (data->path[i++])
	{
		path = ft_strjoin(data->path[i - 1], cmd);
		printf("%s\n", path);
		if (access(path, F_OK/*  | X_OK */) == 0)
		{
			printf("ok");
			return (path);
		}
	}
	return (NULL);
}

// why malloc doesn't need typecast first 

void	exec_cmds(t_data *data)
{
	size_t	i;
	// int8_t	fd;
	// int8_t	pipe_fd[2];
	char	*path;

	i = 1;
	/* for (int32_t i = 0;data->path[i];i++)
		printf("%s\n", data->path[i]); */
	while (i < (size_t)data->argc - 2)
	{
		path = find_path(data, i);
		printf("%s\n", path);
		// fd = fork();
		// if (fd == 0)
		// {
		// 	;
		// }
		i++;
	}
}

void	display_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

#ifdef BONUS // for multiple arguments
bool	input_handler(int32_t argc)
{
	if (argc < 3)
		return (display_error("Needs input file, at least one \
									cmd and an output file"), false);
	return (true);
}

#else // for exactly 4 arguments (+ program name)
void	input_handler(int32_t argc)
{
	if (argc != 5)
		display_error("Needs to be exactly 4 arguments");
}
#endif

int32_t	main(int argc, char **argv, char **envp)
{
	t_data	data;

	input_handler(argc);
	if (!open(argv[1], O_RDONLY))
		display_error("First input file is wrong");
	init_data(argc, argv, &data, envp);
	exec_cmds(&data);
	return (0);
}
