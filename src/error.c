/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:46 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/30 16:40:20 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Handles errors where errno is set
 */
void	errno_handling(char *str, t_pipex *pipex)
{
	free_all(pipex);
	perror(str);
	exit(EXIT_FAILURE);
}

/*
 * Handles errors where errno is not set
 */
void	error_handling(char *str, t_pipex *pipex)
{
	free_all(pipex);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
