/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:46 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/27 18:15:17 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * If array of strings exists, frees all elements in it and then 
 * the pointer to the array of strings.
 */
void free_char_array(char **arr)
{
	int i;
	
	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

/*
 * Handles errors where errno is set
 */
void	errno_handling(char *str, t_pipex *pipex)
{
	free_char_array(pipex->paths);
	perror(str);
	exit(EXIT_FAILURE);
}

/*
 * Handles errors where errno is not set
 */
void	error_handling(char *str, t_pipex *pipex)
{
	free_char_array(pipex->paths);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
