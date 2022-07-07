/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:39:28 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/08 01:04:23 by mialbert         ###   ########.fr       */
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
			free (data()->path[0]);
			data()->path[0] = ft_substr(data()->path[0], 5, \
							ft_strlen(data()->path[0]) - 5);
		}
		envp++;
	}
}

/**
 * Declares a static struct pointer that points to memory allocated on the heap,
 * where the contents of the struct will be initialised. 
 * This is essentially a makeshift global struct without being a global struct.
 * @return the struct, so you can access the members of it by calling this function
 * ex: data()->path
 */
t_data	*data(void)
{
	static t_data	*data1;

	if (!data1)
	{
		data1 = malloc(sizeof(t_data));
		if (!data1)
			display_error("data malloc failed in init_static()", true);
	}
	return (data1);
}
