/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:00 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/12 14:16:06 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Splits args from the arg_numth argument vector. Cycles through available
 * paths appending the cmd name to each path name until a successful match is
 * found then attempts to execute using execve(). Also attempts execution
 * with the raw argument name in case path (/bin/cat) is given as argument.
 */
void	parse_command(t_pipex *pipex)
{
	int		i;
	char	*full_path;
	char	*av_path;

	i = -1;
	av_path = pipex->av[pipex->i];
	dprintf(2, "command %s\n", pipex->av[pipex->i]);
	parse_args(pipex, av_path);
	if (pipex->args == NULL)
		error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
	if (ft_strchr(av_path, '/'))
	{
		full_path = ft_strdup(av_path);
		try_command(pipex, full_path);
	}
	while (pipex->paths[++i] && av_path[0] != '.')
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
	// dprintf(2, "cmd tot: %d\n", p->cmd_total);
	if (p->is_here_doc)
		handle_here_doc(p);
	else
		p->prevfd = p->infile_fd;
	// dprintf(2, "i: %d\n", p->i);
	while (++p->i - p->is_here_doc <= p->cmd_total)
	{
		pipe(p->pipefd);
		p->pid = fork();
		if (p->pid == 0)
		{
			close_safe(p->pipefd[0]);
			dup2_io(p->prevfd, p->pipefd[1]);
			parse_command(p);
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
	p->last_pid = fork();
	if (p->last_pid == 0)
	{
		dup2_io(p->prevfd, p->outfile_fd);
		parse_command(p);
	}
	if (p->prevfd != STDIN_FILENO)
	{
		// dprintf(2, "check\n");
		close_safe(p->prevfd);
		// close_safe(p->outfile_fd);
	}
}

/*
 * Waits for number of children that have been created
 */
void	wait_children(t_pipex *pipex)
{
	int	i;
	int	status;
	int	pid;

	i = -1;
	while (++i < pipex->cmd_total /* + pipex->is_here_doc */) // + here_doc?
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pipex->last_pid)
			pipex->last_status = WEXITSTATUS(status);
		if (pid == -1)
			errno_handling(NULL, pipex, status);
	}
}

void	execute_pipex(t_pipex *p)
{
	fork_loop(p);
	last_command(p);
	wait_children(p);
}
