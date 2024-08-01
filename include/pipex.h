/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:09:23 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/01 18:08:39 by thopgood         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

// Errors
# define ERR_ARGS "Too few arguments\n"
# define ERR_INVALID_ARG "Invalid argument: Empty string\n"
# define ERR_MALLOC "Malloc error\n"
# define ERR_CMDNOTFOUND "command not found\n"
# define ERR_NOFILE "No such file or directory\n"
# define PIP_STR "pipex: "
# define PIP_STR_LEN 7

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	char **args;  // ! malloc
	char **paths; // ! malloc
	int		is_here_doc;
	int		cmd_total;
	int		i;
	int		infile_fd;
	int		outfile_fd;
	int		pipefd[2];
	int		prevfd;
	pid_t	pid;
	pid_t	last_pid;
	int		last_status;
	// int 	exit_status;
}			t_pipex;

void		parse_args(t_pipex *pipex);
void		parse_paths(t_pipex *pipex);
void		open_files(t_pipex *pipex);
void		execute_pipex(t_pipex *p);
void		errno_handling(char *str, t_pipex *pipex, int exit_status);
void		error_handling(char *var_str, char *err_str, t_pipex *pipex,
				int exit_status);
void		free_char_array(char **arr);
void		close_safe(int fd);
void		free_all(t_pipex *pipex);
int			ret_arr_index(char **arr, char *str);
void		dup2_io(int read_fd, int write_fd);
void		try_command(t_pipex *pipex, char *file);

#endif