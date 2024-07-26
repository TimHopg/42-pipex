/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/26 12:13:39 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void validate_args(char **av, )

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
	while (++i < pipex->fork_total)
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
	pipex->child_pids = ft_calloc(pipex->fork_total, sizeof(pid_t));
	if (pipex->child_pids == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

// TODO how to find PATH on different systems

int	main(int ac, char **av)
{
	// t_pipex	pipex;

	// ft_bzero(&pipex, sizeof(pipex));
	// parse_args(ac, av, &pipex);
	// open_files(ac, av, &pipex);
	// open_infile(ac, av, &pipex);
	

	(void)ac;
	(void)av;

	int pfd[2];
	if (pipe(pfd) == -1)
		return 1;

	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	
	char *flags[5] = {"ping", "-c", "2", "google.com", NULL};
	char *cmd = "/sbin/ping";

	if (pid1 == 0) 
	{
		dup2(pfd[1], STDOUT_FILENO); // ! What is this doing? (errno)
		close(pfd[0]); // close read end, not being used
		close(pfd[1]); // dup2 has created new file descriptor so this should be closed
		if (execve(cmd, flags, NULL) < 0)
		{
			ft_printf("here: ");
			perror(NULL);
		}
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 3; // !
	
	char *flags2[3] = {"grep", "round", NULL};
	if (pid2 == 0)
	{
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		if (execve("/usr/bin/grep", flags2, NULL) < 0)
		{
			perror(NULL);
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);



	// initialise_child_pids(&pipex);
	// create_forks(&pipex);
	// if (wait_for_children(&pipex) == -1)
	// {
	// 	free(pipex.child_pids);
	//     ft_printf("Error waiting for children\n");
	// }
	// else
	// 	ft_printf("All children have terminated\n");
	// free(pipex.child_pids);
	// int fd[2];
	// pid1 = fork();
	// pid2 = fork();
	// ft_printf("pid1: %d, pid2:%d\n", pid1, pid2);
	// return (0);





	
	// * pipe creates two fd's 1 write and 0 read to allow both sides of a fork
	// * to communicate
}
