/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:09:23 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/14 12:19:04 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Errors
# define ERR_ARGS "Too few arguments\n"
# define ERR_INVALID_ARG "Invalid argument: Empty string\n"
# define ERR_MALLOC "Malloc error\n"
# define ERR_CMDNOTFOUND "command not found\n"
# define ERR_NOFILE "No such file or directory\n"
# define PIP_STR "pipex: "
# define PIP_STR_LEN 7
# define ERREXECCMD 126

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	char	**args;
	char	**paths;
	int		is_here_doc;
	char	*delim;
	size_t	delim_len;
	int		cmd_total;
	int		i;
	int		infile_fd;
	int		outfile_fd;
	int		pipefd[2];
	int		prevfd;
	pid_t	pid;
	pid_t	last_pid;
	int		last_status;
}			t_pipex;

void		execute_pipex(t_pipex *p);
int		handle_here_doc(t_pipex *p);
void		try_command(t_pipex *pipex, char *file);
int			ret_arr_index(char **arr, char *str);
void		dup2_io(int read_fd, int write_fd, t_pipex *p);
void		prepare_args(t_pipex *pipex);
void		parse_paths(t_pipex *pipex);
void		parse_args(t_pipex *pipex, char *str);
void		open_files(t_pipex *pipex);
void		close_safe(int fd);
void		free_char_array(char **arr);
void		free_all(t_pipex *pipex);
void		errno_handling(char *str, t_pipex *pipex, int exit_status);
void		error_handling(char *var_str, char *err_str, t_pipex *pipex,
				int exit_status);

#endif