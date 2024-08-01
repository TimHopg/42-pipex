/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:00 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/01 11:47:51 by thopgood         ###   ########.fr       */
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
void	parse_command(t_pipex *pipex)
{
	int		i;
	char	*full_path;

	i = -1;
	pipex->args = ft_split(pipex->av[pipex->i], ' ');
	if (pipex->args == NULL)
		error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
	try_command(pipex, pipex->av[pipex->i]);
	while (pipex->paths[++i])
	{
		full_path = ft_strjoin(pipex->paths[i], pipex->args[0]);
		if (full_path == NULL)
			error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
		try_command(pipex, full_path);
		free(full_path);
	}
	error_handling(pipex->args[0], ERR_CMDNOTFOUND, pipex, 127);
}

/*
 * Main loop to redirect infile to STDIN and then to each subsequent command
 */
void	fork_loop(t_pipex *p)
{
	p->prevfd = p->infile_fd;
	while (++p->i <= p->cmd_total)
	{
		pipe(p->pipefd);
		p->pid = fork();
		if (p->pid == 0)
		{
			close_safe(p->pipefd[0]); // ! why?
			dup2_io(p->prevfd, p->pipefd[1]);
			parse_command(p);
			exit(1); // !
		}
		close_safe(p->pipefd[1]);
		if (p->prevfd != STDIN_FILENO)
			close_safe(p->prevfd);
		p->prevfd = p->pipefd[0];
	}
}

void wait_children(t_pipex *pipex)
{
	int i;
	int status;
	int pid;

	i = -1;
	while (++i < pipex->cmd_total)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pipex->last_pid)
			pipex->last_status = WEXITSTATUS(status);
		if (pid == -1)
			errno_handling(NULL, pipex, status);
	}
}

/*
 * Handles last iteration of pipex to redirect output to outfile.
 */
void	last_command(t_pipex *p)
{
	p->last_pid = fork();
	if (p->last_pid == 0)
	{
		dup2_io(p->prevfd, p->outfile_fd);
		parse_command(p);
		exit(1); // !
	}
	if (p->prevfd != STDIN_FILENO)
		close_safe(p->prevfd);
}

void	execute_pipex(t_pipex *p)
{
	fork_loop(p);
	last_command(p);
	wait_children(p);
}
