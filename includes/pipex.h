/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/0nal
8 18:51:44 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/29 19:17:39 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../libs/libft/srcs/libft.h"

typedef struct s_data
{
	int32_t	argc;
	char	**argv; // free this
	char	**path; // free this
	char	**full_cmd; // free this
}	t_data;

// void	init_data(int argc, char **argv, t_data *data, char **envp);
t_data	*data(void);
void	init_data(int32_t argc, char **argv, char **envp);
void	check_error(void *error_code, char *error_msg, bool yeet);
void	input_handler(int32_t argc);
void	free_at_exit(void);

#endif
