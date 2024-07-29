/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:00 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 18:06:42 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static char	*cmd_path(char **paths, char *cmd)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	while (*paths)
	{
		if (ft_strcmp(*paths, cmd, ft_strlen(*paths)) == 0)
		{
			if (access(cmd, X_OK | F_OK) == 0)
			{
				return (cmd);
			}
			else
			{
				return (NULL);
			}
		}
		command = ft_strjoin(*paths, cmd);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	child_dump(t_pipex d)
{
	pipe_msg(d.cmd_args[0]);
	child_free(&d);
	pipe_close(&d);
	free_parent(&d);
	exit(EXIT_FAILURE);
}

static void	ft_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_pipex d, char **argv, char **envp)
{
	d.pid = fork();
	if (!d.pid)
	{
		if (d.id_n == 0)
			ft_dup2(d.infile, d.pipes[1]);
		else if (d.id_n == d.cmd_nbr - 1)
		{
			ft_dup2(d.pipes[2 * d.id_n - 2], d.outfile);
		}
		else
		{
			ft_dup2(d.pipes[2 * d.id_n - 2], d.pipes[2 * d.id_n + 1]);
		}
		pipe_close(&d);
		d.cmd_args = ft_split(argv[2 + d.here_doc + d.id_n], ' ');
		d.cmd = cmd_path(d.cmd_paths, d.cmd_args[0]);
		if (!d.cmd)
		{
			child_dump(d);
		}
		execve(d.cmd, d.cmd_args, envp);
		child_free(&d);
		error_msg("execve");
	}
}
