/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:44:55 by mialbert          #+#    #+#             */
/*   Updated: 2023/03/04 23:47:42 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (!argc_check(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argc, argv, envp);
	exec_cmds(&data, envp);
	free_at_exit(&data);
	return (0);
}
