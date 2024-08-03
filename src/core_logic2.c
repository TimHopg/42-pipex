/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:10:34 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/03 17:30:52 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * If access to the file is available, execve is called and the process will
 * terminate, if not, nothing happens.
 */
void	try_command(t_pipex *pipex, char *file)
{
	// dprintf(2, "file: %s\n", file);
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == 0)
		{
			execve(file, pipex->args, pipex->envp);
			free(file);
			errno_handling(NULL, pipex, EXIT_FAILURE);
		}
		else
			errno_handling(NULL, pipex, ERREXECCMD);
			// perror("pipex: ");
	}
}
