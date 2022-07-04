/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:48:54 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/02 08:11:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
