/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:24:54 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/13 17:32:15 by thopgood         ###   ########.fr       */
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
		if (!pipex->av[i][0] && (!pipex->is_here_doc && i != 2))
			error_handling(NULL, ERR_INVALID_ARG, pipex, EXIT_FAILURE);
	}
}

/*
 * Checks there are sufficient args, both for "here_doc" and not.
 * Sets pipex->here_doc field to TRUE if first arg == "here_doc"
 * Adds number of forks required (no. of cmds) to pipex struct.
 */
void	prepare_args(t_pipex *p)
{
	if (p->ac < 5)
		error_handling(NULL, ERR_ARGS, p, EXIT_FAILURE);
	else if (!ft_strncmp(p->av[1], "here_doc", 9))
	{
		if (p->ac < 6)
			error_handling(NULL, ERR_ARGS, p, EXIT_FAILURE);
		p->is_here_doc = true;
		p->delim = p->av[2];
		p->delim_len = ft_strlen(p->delim);
	}
	empty_string_check(p);
	p->cmd_total = p->ac - p->is_here_doc - 3;
	p->i = 1 + p->is_here_doc;
}

/*
 * Adds slash to end of path if it doesn't already exist
 */
void	add_slash(char **paths)
{
	int		i;
	char	*temp;

	i = -1;
	while (paths[++i])
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
 ! struct. If environment is NULL or no PATH is set, the default of /usr/bin
 ! and /bin is used (as is the case on most Linux systems) CHECK THIS
 */
void	parse_paths(t_pipex *p)
{
	int		i;
	int		path_len;
	char	*default_path;

	default_path = "/usr/bin:/bin";
	path_len = ft_strlen("PATH=");
	i = ret_arr_index(p->envp, "PATH=");
	if (i < 0)
		p->paths = ft_split(default_path, ':');
	else
		p->paths = ft_split(p->envp[i] + path_len, ':');
	if (p->paths == NULL)
		error_handling(NULL, ERR_MALLOC, p, EXIT_FAILURE);
	add_slash(p->paths);
}
