/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:39:28 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/01 17:46:20 by mialbert         ###   ########.fr       */
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