/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:48 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/14 15:42:31 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *p)
{
	char	*line;
	int		read;

	line = NULL;
	close_safe(p->outfile_fd);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		read = get_next_line(STDIN_FILENO, &line);
		if (read == -1)
			error_handling(NULL, ERR_MALLOC, p, EXIT_FAILURE); // !
		if (read == 0 || (!ft_strncmp(line, p->delim, p->delim_len)
				&& (line[p->delim_len] == '\n' || line[p->delim_len] == '\0')))
		{
			free(line);
			close_safe(p->pipefd[1]);
			break ;
		}
		ft_putstr_fd(line, p->pipefd[1]);
		free(line);
	}
	free_all(p);
	close_safe(p->pipefd[1]);
}

int	handle_here_doc(t_pipex *p)
{
	pid_t	pid;

	if (pipe(p->pipefd) == -1)
		return (perror(NULL), EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		close_safe(p->pipefd[0]);
		close_safe(p->pipefd[1]);
		return (perror(NULL), EXIT_FAILURE); // !
	}
	if (pid == 0)
	{
		close_safe(p->pipefd[0]);
		here_doc(p);
		exit(EXIT_SUCCESS);
	}
	close_safe(p->pipefd[1]);
	p->prevfd = p->pipefd[0];
	return (EXIT_SUCCESS);
}
