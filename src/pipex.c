/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/01 11:59:11 by thopgood         ###   ########.fr       */
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
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
}

// TODO how to find PATH on different systems
// TODO check on linux if outfile creates non existent file
// TODO when creating pipes if later pipes fail, close the earlier ones
// TODO Temp2 for potential errors
// * sometimes appends to outfile?! maybe the way outfile is created?
// 	* Done I think
// ! free args array after exec call? necessary or not?
// TODO separate bonus
// ? is it necessary to free malloc'd memory after an exec call?
// TODO check every failure for leaks or fd leaks
// TODO waitpid()

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	initialise_pipex_struct(ac, av, envp, &pipex);
	parse_args(&pipex);  // validates args
	open_files(&pipex);  // opens file descriptors
	parse_paths(&pipex); // creates array of paths
	execute_pipex(&pipex);
	free_all(&pipex);
	exit(pipex.last_status);
}
