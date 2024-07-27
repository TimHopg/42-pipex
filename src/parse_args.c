/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:24:54 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/27 18:25:12 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Checks for empty strings and exits with error message if encountered.
 */
void	empty_string_check(int ac, char **av, t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (!av[i][0])
			error_handling(ERR_INVALID_ARG, pipex);
	}
}

/*
 * Checks there are sufficient args, both for "here_doc" and not.
 * Sets pipex->here_doc field to TRUE if first arg == "here_doc"
 * Adds number of forks required (no. of cmds) to pipex struct.
 */
void	parse_args(int ac, char **av, t_pipex *pipex)
{
	if (ac < 5)
		error_handling(ERR_ARGS, pipex);
	else if (!ft_strncmp(av[1], "here_doc", HERE_DOC_LEN))
	{
		if (ac < 6)
			error_handling(ERR_ARGS, pipex);
		pipex->is_here_doc = TRUE;
	}
	empty_string_check(ac, av, pipex); // ! should this only check files? can it ignore cmds?
	pipex->cmd_total = ac - pipex->is_here_doc - 3;
	pipex->pipe_total = ac - pipex->is_here_doc - 4;
}

/*
 * Adds slash to end of path if it doesn't already exist
 */
void add_slash(char **paths)
{
	int i;

	i = -1;
	char *temp;
	while(paths[++i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			temp = ft_strjoin(paths[i], "/");
			free(paths[i]);
			paths[i] = temp;
		}
	}
}

/*
 * Iterates through environment variables until PATH= is found then
 * separates them by colon and adds them to array of strings 'path' in
 * struct.
 */
void parse_paths(t_pipex *pipex, char **envp)
{
	int path_len;
	path_len = ft_strlen("PATH=");
	while(*envp && ft_strncmp(*envp, "PATH=", path_len) != 0)
		envp++;
	pipex->paths = ft_split(*envp + path_len, ':');
	add_slash(pipex->paths);
}
