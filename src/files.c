/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:14:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/25 17:14:26 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_infile(int ac, char **av, t_pipex *pipex)
{
	(void)ac;
	if (pipex->is_here_doc)
	{
		(void)0;
	}
	else
	{
		pipex->infile_fd = open(av[1], O_RDONLY);
		if (pipex->infile_fd < 0)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
}
