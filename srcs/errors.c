/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:48:54 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/14 22:23:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_at_exit(t_data *data)
{
	if (data->argv)
		free_2d_guard(&data->argv);
	if (data->full_cmd)
		free_2d_guard(&data->full_cmd);
	if (data->path)
		free_2d_guard(&data->path);
}

/**
 * Perror uses the errno variable, which is set with an error message
 * by the last malfunctioning function
 * @param error_msg Including an error message of my own.
 * @param yeet If true, this program will exit.
 */
void	display_error(t_data *data, char *error_msg, bool yeet)
{
	perror(error_msg);
	if (yeet == true)
	{
		free_at_exit(data);
		exit(EXIT_FAILURE);
	}
}

/**
 * BONUS is defined by a -D preprocessor flag with a value of 1 in my makefile 
 * if "make bonus" is used. Otherwise it will not be defined 
 * and the other function would be used.
 * @param argc the amount of command line arguments used. 
 * Mandatory part should only use one infile, outfile and 2 commands.
 */
#ifdef BONUS // for multiple arguments
bool	input_handler(int32_t argc)
{
	if (argc < 3)
		return (ft_putendl_fd("Needs input file, at least one \
								cmd and an output file", STDERR_FILENO), false);
	return (true);
}

#else // for one infile, outfile and 2 commands + program name.
bool	input_handler(int32_t argc)
{
	if (argc != 5)
		return (ft_putendl_fd("Needs to be exactly 4 arguments", STDERR_FILENO), false);
	return (true);
}
#endif
