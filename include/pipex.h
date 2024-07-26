/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:09:23 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/25 17:14:35 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HERE_DOC_LEN 9
# define TRUE 1
# define FALSE 0

// Errors
# define ERR_ARGS "Too few arguments\n"
# define ERR_INVALID_ARG "Invalid argument: Empty string\n"

typedef struct s_pipex
{
	pid_t	*child_pids;
	int		fork_total;
	int		num_children;
	int		is_here_doc;
	int		infile_fd;
	int		outfile_fd;
	// char				*env_path;
	// char				**cmd_paths;
	// char				*cmd;
	// char				**cmd_args;
	// int					outfile;
	// int					here_doc;
	// int					cmd_nbr;
	// int					pipe_nbr;
	// int					*pipes;
	// int					id_n;
	// pid_t				pid;
}			t_pipex;

void		parse_args(int ac, char **av, t_pipex *pipex);
void		open_infile(int ac, char **av, t_pipex *pipex);

#endif