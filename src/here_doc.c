/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:48 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/07 18:16:38 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *p)
{
	char	*line;

    line = NULL;
    ft_putstr_fd("here_doc> ", 1);
	while (get_next_line(STDIN_FILENO, line))
	{
        // if (line == 0) // ! error from GNL
		if (ft_strncmp(line, p->delim, p->delim_len)
			&& line[p->delim_len] == '\n')
        {
            free(line);
            close_safe(p->pipefd[1]);
        }
        ft_putstr_fd(line, p->pipefd[1]);
        free(line);
		ft_putstr_fd("here_doc> ", 1);
	}
}

void	handle_here_doc(t_pipex *p)
{
	pipe(p->pipefd);
	if (fork() == 0)
	{
		close_safe(p->pipefd[0]);
		here_doc(p);
		exit(0); // !
	}
	close_safe(p->pipefd[1]);
	p->prevfd = p->pipefd[0];
}
