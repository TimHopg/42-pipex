/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/31 16:48:29 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void set_shell_str(t_pipex *pipex)
{
	int i;

	i = ret_arr_index(pipex->envp, "SHELL=");
	if (i >= 0)
		pipex->shell = ft_strrchr(pipex->envp[i], '/') + 1;
}

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
	set_shell_str(pipex);
}

// TODO how to find PATH on different systems
// TODO check on linux if outfile creates non existent file
// TODO when creating pipes if later pipes fail, close the earlier ones
// TODO Temp2 for potential errors
// * sometimes appends to outfile?! maybe the way outfile is created? Done I think
// ! free args array after exec call? necessary or not?
// TODO separate bonus
// ? is it necessary to free malloc'd memory after an exec call?
// TODO check every failure for leaks or fd leaks

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	for(int i = 0; envp[i]; i++)
		ft_printf("%s\n", envp[i]);
	initialise_pipex_struct(ac, av, envp, &pipex);
	parse_args(&pipex);  // validates args
	open_files(&pipex);  // opens file descriptors
	parse_paths(&pipex); // creates array of paths
	execute_forks_and_pipes(&pipex);
	free_all(&pipex);
}
