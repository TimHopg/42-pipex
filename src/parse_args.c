/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:24:54 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/25 18:12:46 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Checks for empty strings and exits with error message if encountered.
 */
void	empty_string_check(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (!av[i][0])
		{
			ft_putstr_fd(ERR_INVALID_ARG, 2);
			exit(EXIT_FAILURE);
		}
	}
}

// Adds vector of commands and number of forks into struct.
/*
 * Checks there are sufficient args, both for "here_doc" and not.
 * Sets pipex->here_doc field to TRUE if first arg == "here_doc"
 * Adds number of forks required (no. of cmds) to pipex struct.
 */
void	parse_args(int ac, char **av, t_pipex *pipex)
{
	if (!ft_strncmp(av[1], "here_doc", HERE_DOC_LEN))
	{
		if (ac < 6)
		{
			ft_putstr_fd(ERR_ARGS, 2);
			exit(EXIT_FAILURE);
		}
		pipex->is_here_doc = TRUE;
	}
	else if (ac < 5)
	{
		ft_putstr_fd(ERR_ARGS, 2);
		exit(EXIT_FAILURE);
	}
	empty_string_check(ac, av);
	pipex->fork_total = ac - pipex->is_here_doc - 3;
}
