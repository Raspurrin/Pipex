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
# include <sys/types.h>
# include <sys/wait.h>
# include "../libs/libft/includes/libft.h"

typedef struct s_data
{
	int32_t	argc;
	char	**argv;
	char	**path;
	char	**full_cmd;
	int32_t	infile;
	int32_t	outfile;
}	t_data;

t_data	*data(t_data *data);
void	exec_cmds(t_data *data, char **envp);
void	init_data(t_data *data, int32_t argc, char **argv, char **envp);
void	display_error(t_data *data, char *error_msg, bool yeet);
bool	argc_check(int32_t argc, char **argv);
void	free_at_exit(t_data *data);
int32_t	inout_files(t_data *data);
#endif
