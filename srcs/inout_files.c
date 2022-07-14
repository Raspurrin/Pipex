/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/14 15:13:32 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#ifdef BONUS
/**
 * A heredoc is a file literal. It is a multi-line string taken from STDIN
 * ended by a delimiter. It is then treated as an input file.
 * I create a temporary file where I store everything until the delimiter
 * is used and then delete it 
 */
static void	here_doc(t_data *data)
{
	char	*line;
	int		i;

	data->infile = open(data->argv[0], O_RDWR | O_CREAT, 0666);
	if (data->infile == -1)
		display_error(data, "Heredoc inout_files, Open infile failed", true);
	// printf("%zu\n", ft_strlen(data->argv[1]));
	// line = get_next_line(STDIN_FILENO);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		i = ft_strncmp(line, data->argv[1], ft_strlen(data->argv[1]) + 1);
		// printf("%d\n", i);
		// ft_putstr_fd(line, 2);
		if (i != 10)
		{
			write (data->infile, line, ft_strlen(line));
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
		// printf("%s %s\n", data->argv[1], line);
	}
	// dup2(data->infile, STDIN_FILENO);
	// unlink("./here_doc");
	data->outfile = open(data->argv[data->argc - 2], O_RDWR | O_CREAT \
														| O_APPEND, 0666);
	if (data->outfile == -1)
		display_error(data, "Bonus inout_files, Open outfile failed", false);
}

int32_t	inout_files(t_data *data)
{
	if (ft_strncmp(data->argv[0], "here_doc", 9) == 0)
		return (here_doc(data), 1);
	else
	{
		data->infile = open(data->argv[0], O_RDONLY, 0666);
		if (data->infile == -1)
			display_error(data, "Bonus inout_files, Open infile failed", \
																	true);
		data->outfile = open(data->argv[data->argc - 2], O_RDWR | O_CREAT \
															| O_TRUNC, 0666);
		if (data->outfile == -1)
			display_error(data, "Bonus inout_files, Open outfile failed", \
																	false);
	}
	return (0);
}

#else
/**
 * Opening the input and output files and redirecting the infile to STDIN.
 * with dup2 I duplicate infile and set it to the value of STDIN,
 * which closes the STDIN stream temporarily. Programs use STDIN and STDOUT
 * as standard, so by redirecting it, the next command will use the input
 * from the infile. 
 */
int32_t	inout_files(t_data *data)
{
	data->infile = open(data->argv[0], O_RDONLY);
	if (data->infile == -1)
		display_error(data, "inout_files, Open infile failed", true);
	data->outfile = open(data->argv[data->argc - 2], O_RDWR | O_CREAT \
														| O_TRUNC, 0666);
	if (data->outfile == -1)
		display_error(data, "inout_files, Open outfile failed", true);
	return (0);
}
#endif

// exact width integer


