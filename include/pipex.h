/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:09:23 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/31 17:14:00 by thopgood         ###   ########.fr       */
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
}			t_pipex;

void		parse_args(t_pipex *pipex);
void		parse_paths(t_pipex *pipex);
void		open_files(t_pipex *pipex);
void		execute_pipex(t_pipex *p);
void		errno_handling(char *str, t_pipex *pipex);
void		error_handling(char *var_str, char *err_str, t_pipex *pipex);
void		free_char_array(char **arr);
void		close_safe(int fd);
void		free_all(t_pipex *pipex);
int			ret_arr_index(char **arr, char *str);

#endif