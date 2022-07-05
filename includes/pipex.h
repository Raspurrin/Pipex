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
	int16_t	argc;
	char	**argv;
	char	**path;
}	t_data;

// void	init_data(int argc, char **argv, t_data *data, char **envp);
t_data	*data(int argc, char **argv, char **envp);
void	display_error(char *error_msg);
void	input_handler(int32_t argc);

#endif
