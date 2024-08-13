/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:14:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/13 17:32:02 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Opens outfile with read/write permissions, creates if it doesn't exist and
 * truncates it (doesn't append)
 */
void	open_outfile(t_pipex *p)
{
	// ! check on linux if this can create a file
	if (p->is_here_doc)
		p->outfile_fd = open(p->av[p->ac - 1], O_RDWR | O_CREAT | O_APPEND,
				0644);
	else
		p->outfile_fd = open(p->av[p->ac - 1], O_RDWR | O_CREAT | O_TRUNC,
				0644);
	if (p->outfile_fd < 0)
		errno_handling(NULL, p, EXIT_FAILURE);
}

/*
 * Opens infile in readonly mode
 */
void	open_infile(t_pipex *p)
{
	if (p->is_here_doc)
		return ; // !
	else
	{
		p->infile_fd = open(p->av[1], O_RDONLY);
		if (p->infile_fd < 0)
		{
			write(2, "pipex: ", 7);
			perror(p->av[1]);
			p->infile_fd = open("/dev/null", O_RDONLY);
			if (p->infile_fd == -1)
				errno_handling(p->av[1], p, EXIT_FAILURE);
		}
	}
}

void	open_files(t_pipex *p)
{
	open_outfile(p);
	open_infile(p);
}
