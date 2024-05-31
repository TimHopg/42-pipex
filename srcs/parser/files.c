/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:57:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 17:28:17 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_infile(t_pipex *pipex, char **argv, int argc)
{
	int	pipes;

	pipes = argc - 5;
	if (pipex->here_doc)
		here_doc(argv[2], pipex, pipes);
	else
		pipex->infile = open(argv[1], O_RDONLY);
}

void	ft_outfile(t_pipex *pipex, char *argv)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
}

int	ft_files(t_pipex *pipex, char **argv, int argc)
{
	ft_infile(pipex, argv, argc);
	ft_outfile(pipex, argv[argc - 1]);
	if (pipex->outfile < 0 || pipex->infile < 0)
		error_msg("Opening(infile OR outfile)");
	return (1);
}
