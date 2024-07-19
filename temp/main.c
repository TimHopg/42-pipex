/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:49:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 17:26:10 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static void	pipe_creation(t_pipex *pipex)
{
	int	ctd;

	ctd = 0;
	while (ctd < (pipex->cmd_nbr) - 1)
	{
		if (pipe(pipex->pipes + 2 * ctd) < 0)
			free_parent(pipex);
		ctd++;
	}
}

void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbr) && pipex->pipe_nbr)
	{
		close(pipex->pipes[i]);
		i++;
	}
}

void	child_wait(int num_cmds)
{
	int		status;
	int		i;
	pid_t	pid;

	i = 0;
	while (i < num_cmds)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			perror("waitpid");
			continue ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	d;

	if (argc < arg_check(argv, &d) || !content_check(argv))
		return (ft_putstr_fd("Too few OR invalid arguments\n", 2), 1);
	ft_files(&d, argv, argc);
	d.cmd_nbr = argc - 3 - d.here_doc;
	d.pipe_nbr = 2 * (d.cmd_nbr - 1);
	d.pipes = (int *)ft_calloc(sizeof(int), d.pipe_nbr);
	if (!d.pipes)
		return (error_msg("err creating pipes"), 1);
	env_paths(&d, envp);
	if (!d.cmd_paths)
		return (free_pipes(&d), 1);
	pipe_creation(&d);
	d.id_n = -1;
	while (++(d.id_n) < d.cmd_nbr)
		child(d, argv, envp);
	pipe_close(&d);
	child_wait(d.cmd_nbr);
	free_parent(&d);
	return (0);
}
