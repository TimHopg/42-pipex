/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:10:49 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 12:00:56 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_paths(char **paths, int i)
{
	int	ctd;

	ctd = 0;
	if (!paths)
		return ;
	while (ctd < i)
	{
		if (paths[i])
			free(paths[i]);
		ctd++;
	}
	free(paths);
}

int	content_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!argv[i][0])
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(char **argv, t_pipex *pipex)
{
	if (argv[1] && !ft_strncmp("here_doc", argv[1], 9))
		return (pipex->here_doc = 1, 6);
	else
		return (pipex->here_doc = 0, 5);
}

int	add_slash(char *slash, char **paths)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
		{
			slash = ft_strjoin(paths[i], "/");
			if (!slash)
				return (free_paths(paths, i), 0);
			free(paths[i]);
			paths[i] = slash;
		}
		i++;
	}
	return (1);
}

char	*env_paths(t_pipex *pipx, char **envp)
{
	char	**paths;
	char	*slash;

	slash = NULL;
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split(*envp + 5, ':');
	if (!paths)
	{
		return (NULL);
	}
	add_slash(slash, paths);
	pipx->cmd_paths = paths;
	return (NULL);
}
