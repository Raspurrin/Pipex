/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:48:54 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/07 04:57:45 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_at_exit(void)
{
	free(data()->argv);
	free(data()->full_cmd);
	free(data()->path);
}

/**
 * Perror uses the errno variable, which is set with an error message
 * by the last malfunctioning function
 * @param error_msg Including an error message of my own.
 * @param error_code Return of function/variable/fd that it's checking.
 * @param exit If true, this program will exit.
 */
void	check_error(void *error_code, char *error_msg, bool yeet)
{
	if ((int32_t)error_code == -1 || error_code == NULL)
	{
		perror(error_msg);
		free_at_exit();
		if (yeet == true)
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
void	input_handler(int32_t argc)
{
	if (argc < 3)
		check_error(-1, "Needs input file, at least one \
									cmd and an output file", true);
}

#else // for one infile, outfile and 2 commands + program name.
void	input_handler(int32_t argc)
{
	if (argc != 5)
		check_error(-1, "Needs to be exactly 4 arguments", true);
}
#endif
