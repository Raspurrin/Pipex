/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:39:28 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/06 03:11:55 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * pipex infile "ls -la" "grep -i something" outfile
 * full_cmd[0]: usr/bin/ls "ls", "-la"
 * full_cmd[1]: usr/bin/grep "-i", "something"
 */
void	init_data(int32_t argc, char **argv, char **envp)
{
	size_t	i;

	i = 0;
	data()->argc = argc;
	data()->argv = malloc((argc) * sizeof(char *));
	while (i++ < (size_t)argc - 1)
		data()->argv[i - 1] = ft_strdup(argv[i]);
	data()->argv[i - 1] = NULL;
	while (*envp != NULL)
	{
		if (!ft_strncmp("PATH", *envp, 4))
		{
			data()->path = ft_split(*envp, ':');
			data()->path[0] = ft_substr(data()->path[0], 5, \
							ft_strlen(data()->path[0]) - 5);
		}
		envp++;
	}
}

t_data	*data(void)
{
	static t_data	*data1;

	if (!data1)
	{
		data1 = malloc(sizeof(t_data));
		if (!data1)
			display_error("data malloc failed in init_static()");
	}
	return (data1);
}
