/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:46 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/31 17:00:43 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Handles errors where errno is set
 */
void	errno_handling(char *str, t_pipex *pipex)
{
	perror(str);
	free_all(pipex);
	exit(EXIT_FAILURE);
}

/*
 * Handles errors where errno is not set
 */
void	error_handling(char *var_str, char *err_str, t_pipex *pipex)
{
	if (pipex->shell)
	{
		write(2, pipex->shell, ft_strlen(pipex->shell));
		write(2, ": ", 2);
	}
	if (var_str)
	{
		write(2, var_str, ft_strlen(var_str));
		write(2, ": ", 2);
	}
	ft_putstr_fd(err_str, 2);
	free_all(pipex);
	exit(EXIT_FAILURE);
}
