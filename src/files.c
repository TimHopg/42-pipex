/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:14:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/27 17:54:12 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_outfile(int ac, char **av, t_pipex *pipex)
{
	// ! check on linux if this can create a file
	pipex->outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
	if (pipex->outfile_fd < 0)
		errno_handling(NULL, pipex);

}

void open_infile(char **av, t_pipex *pipex)
{
	if (pipex->is_here_doc)
	{
		(void)0; // !
	}
	else
	{
		pipex->infile_fd = open(av[1], O_RDONLY);
		if (pipex->infile_fd < 0)
			errno_handling(NULL, pipex);
	}
}

void		open_files(int ac, char **av, t_pipex *pipex)
{
	open_outfile(ac, av, pipex);
	open_infile(av, pipex);
}
