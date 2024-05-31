/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 17:22:20 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../srcs/lib/gnl/gnl.h"
# include "../srcs/lib/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex	t_pipex;

struct					s_pipex
{
	char				*env_path;
	char				**cmd_paths;
	char				*cmd;
	char				**cmd_args;
	int					infile;
	int					outfile;
	int					here_doc;
	int					cmd_nbr;
	int					pipe_nbr;
	int					*pipes;
	int					id_n;
	pid_t				pid;
};

//==================== Cleaning ===========================//
void					error_msg(char *str);
void					free_parent(t_pipex *pipx);
void					free_pipes(t_pipex *pipex);
void					pipe_msg(char *arg);
void					pipe_close(t_pipex *pipex);
void					child_free(t_pipex *pipex);

//==================== Files ===========================//
void					ft_infile(t_pipex *pipex, char **argv, int argc);
void					ft_outfile(t_pipex *pipex, char *argv);
void					here_doc(char *dli, t_pipex *pipx, int pipe_nbr);
int						ft_files(t_pipex *pipex, char **argv, int argc);

//==================== Args ===========================//
int						arg_check(char **argv, t_pipex *pipex);

//==================== Processes ===========================//
void					child(t_pipex d, char **argv, char **envp);

//==================== Parser ===========================//
char					*env_paths(t_pipex *pipx, char **envp);
int						content_check(char **argv);
int						is_space(char c);
#endif
