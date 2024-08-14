/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/14 12:44:57 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * also sets FDs as -1 (not in use)
 */
void	initialise_pipex_struct(int ac, char **av, char **envp, t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(*pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->infile_fd = FD_CLOSED;
	pipex->outfile_fd = FD_CLOSED;
}

// TODO separate bonus
// TODO check every failure for leaks or fd leaks
// TODO check for open files with lsof
// TODO appending NULL to the end of argv in execve
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	initialise_pipex_struct(ac, av, envp, &pipex);
	prepare_args(&pipex);
	open_files(&pipex);
	parse_paths(&pipex);
	execute_pipex(&pipex);
	free_all(&pipex);
	exit(pipex.last_status);
}
