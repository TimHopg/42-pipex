/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:03:13 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 12:28:04 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	pipe_msg(char *arg)
{
	if (!arg)
		arg = "{COMMAND}";
	ft_putstr_fd("Error on:\t", 2);
	ft_putstr_fd(arg, 2);
	write(2, "\n", 1);
}

void	free_parent(t_pipex *pipex)
{
	int	ctd;

	ctd = 0;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	while (pipex->cmd_paths[ctd] && pipex->cmd_paths)
	{
		free(pipex->cmd_paths[ctd]);
		ctd++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipes);
}

void	free_pipes(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	if (pipex->pipes)
		free(pipex->pipes);
	error_msg("Error on Envp");
	exit(1);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i] && pipex->cmd_args)
	{
		if (pipex->cmd_args[i])
			free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}
