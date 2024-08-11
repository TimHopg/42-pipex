/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:48 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/11 22:35:52 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *p)
{
	char	*line;
	int		read;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		read = get_next_line(STDIN_FILENO, &line);
		// if (read == -1) // ! error from GNL
		if (read == 0 || (!ft_strncmp(line, p->delim, p->delim_len)
			&& (line[p->delim_len] == '\n' || line[p->delim_len] == '\0')))
		{
			free(line);
			// close_safe(p->pipefd[1]);
			break ;
		}
		ft_putstr_fd(line, p->pipefd[1]);
		free(line);
	}
	close_safe(p->pipefd[1]);
}

void	handle_here_doc(t_pipex *p)
{
	pid_t pid;

	if (pipe(p->pipefd) == -1)
	{
		exit(0); // !
	}
	pid = fork();
	if (pid == -1)
	{
		exit(0); // !
	}
	if (pid == 0)
	{
		close_safe(p->pipefd[0]);
		here_doc(p);
		exit(EXIT_SUCCESS); // !
	}
	close_safe(p->pipefd[1]);
	waitpid(pid, NULL, 0);
	p->prevfd = p->pipefd[0];
}
