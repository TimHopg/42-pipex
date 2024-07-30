/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:00 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/30 15:50:26 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Splits args from the arg_numth argument vector. Cycles through available
 * paths appending the cmd name to each path name until a successful match is
 * found then executes using execve().
 ! If no successful path is found?
 ! change from arg_num to p->i and test
 */
void	execute_command(t_pipex *pipex, int arg_num)
{
	int		i;
	char	*full_path;

	i = -1;
	pipex->args = ft_split(pipex->av[arg_num], ' '); // ! malloc
	while (pipex->paths[++i])
	{
		full_path = ft_strjoin(pipex->paths[i], pipex->args[0]); // ! malloc
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, pipex->args, pipex->envp);
			free(full_path);
			errno_handling(NULL, pipex);
		}
		free(full_path);
	}
	// ! command not found function goes here?
}

/*
 * Sets STDIN to read_fd and STDOUT to write_fd.
 ! why?
 */
void	dup2_io(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	if (read_fd != STDIN_FILENO)
		close_safe(read_fd); // ! why?
	dup2(write_fd, STDOUT_FILENO);
	close_safe(write_fd);
}

/*
 * Main loop to redirect infile to STDIN and then to each subsequent command
 */
void	fork_loop(t_pipex *p)
{
	p->prevfd = p->infile_fd;
	while (++p->i < p->cmd_total)
	{
		pipe(p->pipefd);
		p->pid = fork();
		if (p->pid == 0)
		{
			close_safe(p->pipefd[0]); // ! why?
			dup2_io(p->prevfd, p->pipefd[1]);
			execute_command(p, p->i + 1);
			exit(1); // !
		}
		close_safe(p->pipefd[1]);
		if (p->prevfd != STDIN_FILENO)
			close_safe(p->prevfd);
		p->prevfd = p->pipefd[0];
	}
}

/*
 * Handles last iteration of pipex to redirect output to outfile.
 */
void	last_command(t_pipex *p)
{
	p->pid = fork();
	if (p->pid == 0)
	{
		dup2_io(p->prevfd, p->outfile_fd);
		execute_command(p, p->i + 1);
		exit(1); // !
	}
	if (p->prevfd != STDIN_FILENO)
		close_safe(p->prevfd);
	while (wait(NULL) > 0)
		;
}

void	execute_forks_and_pipes(t_pipex *p)
{
	fork_loop(p);
	last_command(p);
}
