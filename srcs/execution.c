/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/07/08 01:46:07 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * Full_cmd contains the cmd with all its flags in seperate elements: "ls -la"
 * It is included in my data struct because it is later used in execve!
 * Cmd takes the first element and joins it with '/': "/ls"
 * Path combines the path with cmd: "usr/bin/ls" and checks its accessibility.
 */
static char	*find_path(size_t	argv_i)
{
	size_t	i;
	char	*cmd;
	char	*path;

	i = 0;
	data()->full_cmd = ft_split(data()->argv[argv_i], ' ');
	cmd = ft_strjoin("/", data()->full_cmd[0]);
	while (data()->path[i++])
	{
		path = ft_strjoin(data()->path[i - 1], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), path);
		else
			free(path);
	}
	free(cmd);
	return (NULL);
}

#ifdef BONUS // With heredoc instead of infile! 
static int32_t	inout_files()
{
	if (ft_strncmp(data()->argv[0], "here_doc", 9) == 0)
	{
		char	*line;

		data()->infile = open(data()->argv[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		if (data()->infile == -1)
			display_error("Heredoc inout_files, Open infile failed: ", true);
		while(ft_strncmp(line, data()->argv[1], ft_strlen(data()->argv[1]) != 0))
		{
			line = get_next_line(STDIN_FILENO);
			write (data()->infile, line, ft_strlen(line));
		}
		data()->outfile = open(data()->argv[data()->argc - 2], O_RDWR | O_CREAT | O_APPEND, 0666);
		if (data()->outfile == -1)
			display_error("Bonus inout_files, Open outfile failed: ", false);
	}
	else 
	{
		data()->infile = open(data()->argv[0], O_RDONLY | O_TRUNC, 0666);
		if (data()->infile == -1)
			display_error("Bonus inout_files, Open infile failed: ", false);
		data()->outfile = open(data()->argv[data()->argc - 2], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (data()->outfile == -1)
			display_error("Bonus inout_files, Open outfile failed: ", false);
	}
	return (1);
}
#else
/**
 * Opening the input and output files and redirecting the infile to STDIN.
 * with dup2 I duplicate infile and set it to the value of STDIN,
 * which closes the STDIN stream temporarily. Programs use STDIN and STDOUT
 * as standard, so by redirecting it, the next command will use the input
 * from the infile. 
 */
static int32_t	inout_files()
{
	data()->infile = open(data()->argv[0], O_RDONLY);
	if (data()->infile == -1)
		display_error("inout_files, Open infile failed: ", false);
	data()->outfile = open(data()->argv[data()->argc - 2], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (data()->outfile == -1)
		display_error("inout_files, Open outfile failed: ", false);
	return (0);
}
#endif

void	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

/**
 * First I find the correct path for the next command in find_path()
 * Execve will execute another program which takes over the entire process.
 * Which is why this is done in a child process. 
 * At the very last itteration, the output is redirected to a file. 
 */
void	child_cmd(size_t i, char **envp, int32_t fd[2])
{
	char	*path;

	path = find_path(i + 1);
	if (i == (size_t)data()->argc - 4)
	{
		if (dup2(data()->outfile, STDOUT_FILENO) == -1)
			display_error("child_cmd, last dup2 failed: ", true);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			display_error("child_cmd, dup2 failed: ", true);
	}
	print_2d_array(data()->full_cmd);
	close(fd[0]);
	close(fd[1]);
	if (execve(path, data()->full_cmd, envp) == -1)
		display_error("execve failed", true); // path doesn't work with error_msg, why? 
}

/**
 * Creating new child processes for each command executed, facilitating
 * inter-process communication with pipes and redirecting output and input
 * from the commands to STDIN and STDOUT with dup2, which will then be used
 * by the next command. Closing the fds so the program doesn't wait for input.
 */
static void	exec_cmds(char **envp)
{
	size_t	i;
	int32_t	pid;
	int32_t	fd[2];

	i = inout_files();
	if (dup2(data()->infile, STDIN_FILENO) == -1)
		display_error("inout_files, dup2 failed: ", true);
	while (i < (size_t)data()->argc - 3) 
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			display_error("fork failed: ", true);
		if (pid == 0)
			child_cmd(i, envp, fd);
		waitpid(pid, NULL, 0);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			display_error("exec_cmds, dup2 failed: ", true);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	close(data()->outfile);
	close(data()->infile);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	input_handler(argc);
	init_data(argc, argv, envp);
	exec_cmds(envp);
	free_at_exit();
	return (0);
}
