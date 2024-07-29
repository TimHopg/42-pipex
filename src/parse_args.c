/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:24:54 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/29 18:53:23 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Checks for empty strings and exits with error message if encountered.
 */
void	empty_string_check(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->ac)
	{
		if (!pipex->av[i][0])
			error_handling(ERR_INVALID_ARG, pipex);
	}
}

/*
 * Checks there are sufficient args, both for "here_doc" and not.
 * Sets pipex->here_doc field to TRUE if first arg == "here_doc"
 * Adds number of forks required (no. of cmds) to pipex struct.
 */
void	parse_args(t_pipex *p)
{
	if (p->ac < 5)
		error_handling(ERR_ARGS, p);
	else if (!ft_strncmp(p->av[1], "here_doc", 9))
	{
		if (p->ac < 6)
			error_handling(ERR_ARGS, p);
		p->is_here_doc = TRUE;
	}
	empty_string_check(p); // ! should this only check files? can it ignore cmds?
	p->cmd_total = p->ac - p->is_here_doc - 3;
	p->pipe_total = p->ac - p->is_here_doc - 4;
	p->i += p->is_here_doc;
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
void parse_paths(t_pipex *p)
{
	int i;

	i = 0;
	int path_len;
	path_len = ft_strlen("PATH=");
	while(p->envp[i] && ft_strncmp(p->envp[i], "PATH=", path_len) != 0)
		i++;
	p->paths = ft_split(p->envp[i] + path_len, ':');
	add_slash(p->paths);
}
