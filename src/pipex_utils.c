/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:48:32 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/31 15:36:30 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * returns the index of array that matches str or -1 if not found.
 */
int	ret_arr_index(char **arr, char *str)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (arr[i] && ft_strncmp(arr[i], str, str_len) != 0)
		i++;
	if (arr[i] == NULL)
		return (-1);
	return (i);
}

/*
 * Closes fd and then sets it to -1.
 */
void	close_safe(int fd)
{
	if (fd != -1)
		close(fd);
	fd = -1;
}

/*
 * If array of strings exists, frees all elements in it and then
 * the pointer to the array of strings.
 */
void	free_char_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

/*
 * Safely frees all memory and closes potentially open file descriptors
 */
void free_all(t_pipex *pipex)
{
	free_char_array(pipex->args);
	free_char_array(pipex->paths);
	close_safe(pipex->infile_fd);
	close_safe(pipex->outfile_fd);
}
