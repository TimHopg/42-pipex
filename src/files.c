/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:14:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/29 18:53:34 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_outfile(t_pipex *p)
{
	// ! check on linux if this can create a file
	p->outfile_fd = open(p->av[p->ac - 1], O_RDWR | O_CREAT, 0644);
		// ! revise these
	if (p->outfile_fd < 0)
		errno_handling(NULL, p);
}

void	open_infile(t_pipex *p)
{
	if (p->is_here_doc)
	{
		(void)0; // !
	}
	else
	{
		p->infile_fd = open(p->av[1], O_RDONLY);
		if (p->infile_fd < 0)
			errno_handling(NULL, p);
	}
}

void	open_files(t_pipex *p)
{
	open_outfile(p);
	open_infile(p);
}
