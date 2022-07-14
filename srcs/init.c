/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:39:28 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/15 01:39:32 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * Initialising argc, argv and paths in my data struct. 
 * @param envp This is a 2D array with all environmental variables.
 * I go through it untill the PATH variable is found and I 
 * initialise a 2D array with all the paths contained in it
 * and substract "PATH=" from the first element.
 */
void	init_data(t_data *data, int32_t argc, char **argv, char **envp)
{
	size_t	i;
	char	*tmp;

	i = 0;
	data->argc = argc;
	data->argv = malloc((argc) * sizeof(char *));
	while (i++ < (size_t)argc - 1)
		data->argv[i - 1] = ft_strdup(argv[i]);
	data->argv[i - 1] = NULL;
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
		{
			data->path = ft_split(*envp, ':');
			tmp = ft_substr(data->path[0], 5, \
							ft_strlen(data->path[0]) - 5);
			free (data->path[0]);
			data->path[0] = tmp;
		}
		envp++;
	}
}
