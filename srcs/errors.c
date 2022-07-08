/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:48:54 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/08 05:01:03 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_at_exit(t_data *data)
{
	if (data->argv)
		free(data->argv);
	if (data->full_cmd)
		free(data->full_cmd);
	if (data->path)
		free(data->path);
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
void	input_handler(t_data *data, int32_t argc)
{
	if (argc < 3)
		display_error(data, "Needs input file, at least one \
									cmd and an output file", true);
}

#else // for one infile, outfile and 2 commands + program name.
void	input_handler(t_data *data, int32_t argc)
{
	if (argc != 5)
		display_error(data, "Needs to be exactly 4 arguments", true);
}
#endif
