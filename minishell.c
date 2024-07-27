// void validate_args(char **av, )

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
	int		cmd_total;
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


static void	which_child(t_pipex *pipex, pid_t terminated_pid, int status,
		int *children_left)
{
	int	i;

	i = -1;
	while (++i < pipex->num_children)
	{
		if (pipex->child_pids[i] == terminated_pid)
		{
			ft_printf("child process (PID: %d) terminated. ", terminated_pid);
			if (WIFEXITED(status))
				ft_printf("Exit status: %d\n", WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				ft_printf("Killed by signal: %d\n", WTERMSIG(status));
			pipex->child_pids[i] = -1;
			--*children_left;
			break ;
		}
	}
}

int	wait_for_children(t_pipex *pipex)
{
	int		status;
	int		children_left;
	pid_t	terminated_pid;

	children_left = pipex->num_children;
	while (children_left > 0)
	{
		terminated_pid = wait(&status);
		if (terminated_pid == -1)
		{
			if (errno == ECHILD) // no more children to wait for
				break ;
			else
			{
				perror("wait failed"); // ! free memory
				return (-1);
			}
		}
		which_child(pipex, terminated_pid, status, &children_left);
	}
	return (0);
}

// ! make sure no nested children
void	create_forks(t_pipex *pipex)
{
	int		i;
	pid_t	pid;
	int		child_num;

	child_num = 0;
	i = -1;
	while (++i < pipex->cmd_total)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			if (ft_printf("Child process %d (PID: %d) started\n", i, getpid()) < 0)
				exit(0); // ! check each write 
			sleep(i + 1);
			exit(i);
		}
		else
			pipex->child_pids[child_num++] = pid;
	}
	pipex->num_children = child_num;
}

void	initialise_child_pids(t_pipex *pipex)
{
	pipex->child_pids = ft_calloc(pipex->cmd_total, sizeof(pid_t));
	if (pipex->child_pids == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}