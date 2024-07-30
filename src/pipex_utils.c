/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:48:32 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/30 15:50:31 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Closes fd and then sets it to -1.
 */
void close_safe(int fd)
{
	if (fd != -1)
		close(fd);
	fd = -1;
}
