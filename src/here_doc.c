/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:48 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/13 12:25:54 by thopgood         ###   ########.fr       */
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
		// if (read == -1) // ! error from GNL
		if (read == 0 || (!ft_strncmp(line, p->delim, p->delim_len)
			&& (line[p->delim_len] == '\n' || line[p->delim_len] == '\0')))
		{
			free(line);
			// close_safe(0);
			// close_safe(1);
			// close_safe(p->pipefd[0]);
			close_safe(p->pipefd[1]);
			break ;
		}
		ft_putstr_fd(line, p->pipefd[1]);
		free(line);
	}
	free_all(p); // ! is this sufficient
	close_safe(p->pipefd[1]);
}

void	handle_here_doc(t_pipex *p)
{
	pid_t pid;

	if (pipe(p->pipefd) == -1)
	{
		errno_handling(NULL, p, EXIT_FAILURE); // !
	}
	pid = fork();
	if (pid == -1)
	{
		errno_handling(NULL, p, EXIT_FAILURE); // !
	}
	if (pid == 0)
	{
		close_safe(p->pipefd[0]);
		here_doc(p);
		exit(EXIT_SUCCESS); // !
	}
	close_safe(p->pipefd[1]);
	waitpid(pid, NULL, 0); // ! this is causing too many waits. Why?
	p->prevfd = p->pipefd[0];
	// close_safe(p->pipefd[0]);
}
