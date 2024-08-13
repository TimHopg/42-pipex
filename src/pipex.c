/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/13 15:36:23 by thopgood         ###   ########.fr       */
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

// TODO Temp2 for potential errors
// ? is it necessary to free malloc'd memory after an exec call?
// TODO separate bonus
// TODO check every failure for leaks or fd leaks
// TODO trues and falses
// ! mismatching quotes?
// TODO check here_doc first input is DELIM
// TODO test with huge here_doc input (whats the benefit of using temp file
// 	TODO over just sending the string?)
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	initialise_pipex_struct(ac, av, envp, &pipex);
	prepare_args(&pipex);
	open_files(&pipex);
	parse_paths(&pipex);

	// ft_printf("delim: %s\n", pipex.delim);
	// ft_printf("command total: %d\n", pipex.cmd_total);

	// dprintf(2, "%d\n", pipex.cmd_total);

	execute_pipex(&pipex);
	free_all(&pipex);
	exit(pipex.last_status);

	// (void)ac;
	// (void)av;
	// (void)envp;

	// char *line;
	// int fd = open("infile", O_RDWR);
	// get_next_line(fd, &line);

	// ft_printf("%s\n", line);
}
