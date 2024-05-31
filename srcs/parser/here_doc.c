/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:26:23 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 18:47:49 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../lib/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	finish_here(t_pipex *pipx)
{
	if (pipx->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(EXIT_FAILURE);
	}
}

void	here_doc(char *dli, t_pipex *pipx, int pipe_nbr)
{
	int		file;
	char	*line;
	int		i;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		error_msg("Error opening here_doc");
	while (1)
	{
		i = -1;
		while (++i < pipe_nbr)
			ft_putstr_fd("pipe ", 1);
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(0);
		if (line == NULL || ft_strcmp(line, dli, ft_strlen(line) - 1) == 0)
			break ;
		ft_putstr_fd(line, file);
		free(line);
	}
	free(line);
	close(file);
	pipx->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipx->infile < 0)
		finish_here(pipx);
}
