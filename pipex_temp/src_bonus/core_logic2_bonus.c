/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:10:34 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/14 17:28:00 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * If access to the file is available, execve is called and the process will
 * terminate, if not, nothing happens.
 */
void	try_command(t_pipex *pipex, char *file)
{
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
	}
}
