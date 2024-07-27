/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/27 18:51:16 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Logic
 * pipex->i; (p->i)
 * while (pipex->i < pipex->cmd_total)
 * if (++(p->i)(?) == 0)
 * 	run infile to cmd 1
 * 	close(pipe[0][1]);
 * 	pipe[1][0]
 * if (i + 1 == cmd_total)
 * 	run outfile
 * else
 * 	int x = p-> i & 2
 * 	run cmd -> cmd process
 * 	pipe[x][0] = read pipe;
 * 	pipe[x][1] = write pipe;
 * 	close
 ? wait
 ? here_doc
 ? 
 */

// void read_from_infile(char **av, t_pipex *pipex)
// {
// 	dup2(pipex->infile_fd, STDIN_FILENO);
// 	close(pipex->infile_fd);

// }


void run_pipex(int ac, char **av, t_pipex *p)
{
	(void)ac;
	(void)av;
	int status;

	char **arr;
	arr = ft_split(av[2], ' '); // "cat -b"
	pid_t child_pids[4];

	while (p->i < p->cmd_total)
	{
		if (p->i < p->pipe_total)
			if (pipe(p->curr_pipe) == -1)
				errno_handling(NULL, p);



		p->pid = fork();
		if (p->pid == -1)
			errno_handling(NULL, p);


		child_pids[p->i] = p->pid;
		ft_printf("pid: %d\n", child_pids[p->i]);

		
		if (p->pid == 0) // child process
		{



			
			if (p->i > 0) // inputs
			{
				if (dup2(p->prev_pipe[0], STDIN_FILENO) < 0)
					errno_handling(NULL, p);
				close(p->prev_pipe[0]);
			}
			else // first iteration
			{
				if (dup2(p->infile_fd, STDIN_FILENO) < 0)
					errno_handling(NULL, p);
				close(p->infile_fd);
			}




			if (p->i < p->pipe_total) // outputs
			{
				if (dup2(p->curr_pipe[1], STDOUT_FILENO) < 0)
					errno_handling(NULL, p);
				close(p->curr_pipe[0]);
				close(p->curr_pipe[1]);
			}
			else
			{
				dup2(p->outfile_fd, STDOUT_FILENO);
				close(p->outfile_fd);
			}


			// ft_printf("child count count:%d\n", p->i);
			// execute program
			execve("/bin/cat", arr, NULL);
			errno_handling("exe, pcve", p);
			exit(1);
		}
		
		// Parent process
		if (p->i > 0)
		{
			close(p->prev_pipe[0]);
			close(p->prev_pipe[1]);
		}
		if (p->i < p->pipe_total) // for all but last iteration
		{
			p->prev_pipe[0] = p->curr_pipe[0];
			p->prev_pipe[1] = p->curr_pipe[1];
		}
		++(p->i);
	}


	if (p->cmd_total > 1)
	{
		close(p->prev_pipe[0]);
		close(p->prev_pipe[1]);
	}

	// for (int x = 0; x < p->i; x++)
	// {
	// 	ft_printf("pid[%d]: %d\n", p->i, child_pids[p->i]);
	// }

	// wait for child processes

	// for (int i = 0; i < p->cmd_total; i++) {
	// 	waitpid(child_pids[p->i], &status, 0);
	// 	// ft_printf("child closed\n");
	// }

	wait(&status);
	printf("%d\n", WEXITSTATUS(status));
	wait(&status);
	printf("%d\n", WEXITSTATUS(status));
	wait(&status);
	printf("%d\n", WEXITSTATUS(status));
	wait(&status);
	printf("%d\n", WEXITSTATUS(status));



	// int i = -1;
	// 		// ft_printf("check\n");
	// while (++i < p->cmd_total)
	// {
	// 	ft_printf("i:%d\n", i);
	// 	wait(NULL);
	// }
}


// TODO how to find PATH on different systems
// TODO check on linux if outfile creates non existent file
// TODO when creating pipes if later pipes fail, close the earlier ones
// ? don't quit when one pipe fails so the following ones still produce an
// ?	output like piping to wc from a file that doesnt exist ( probably not a good idea)
// ! You can create a pipe before each process. or a circular buffer of two 
// !	pipes and reuse the same FDs

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	(void)ac;
	(void)av;
	(void)envp;
	ft_bzero(&pipex, sizeof(pipex));
	parse_args(ac, av, &pipex);
	open_files(ac, av, &pipex);
	parse_paths(&pipex, envp);
	errno_handling(NULL, &pipex);


	// for (int i = 0; envp[i]; i++)
	// {
	// 	ft_printf("%s\n", envp[i]);
	// }

	// run_pipex(ac, av, &pipex);

	// int fd[2];
	// pipe(fd);

	// ft_printf("%d:fd[0] %d:fd[1]\n", fd[0], fd[1]);
	// close(fd[1]);
	// ft_printf("%d:fd[0] %d:fd[1]\n", fd[0], fd[1]);


	// char **arr;
	// arr = ft_split(av[2], ' '); // ! MALLOC'D MEMORY
	// if (arr == NULL)
	// 	error_handling(ERR_MALLOC);
	// for (int i = 0; arr[i]; i++)
	// {
	// 	ft_printf("%s\n", arr[i]);
	// }

	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(pipex.infile_fd, STDIN_FILENO);

	// 	dup2(pipex.outfile_fd, STDOUT_FILENO);
	// 	close(pipex.infile_fd);
	// 	close(pipex.outfile_fd);
	// 	execve("/bin/cat", arr, NULL);
	// 	perror("execve");
	// 	exit(1);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	close(pipex.infile_fd);
	// 	close(pipex.outfile_fd);
	// }
	// return 0;



	
	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(pipex.infile_fd, STDIN_FILENO);
	// 	dup2(pipex.outfile_fd, STDOUT_FILENO);
	// 	close(pipex.infile_fd);
	// 	close(pipex.outfile_fd);
	// 	char *cmd[2] = {"cat", NULL};
	// 	execve("/bin/cat", cmd, NULL);
	// 	perror("execve");
	// 	exit(1);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	close(pipex.infile_fd);
	// 	close(pipex.outfile_fd);
	// }
	// return 0;

	

	// (void)ac;
	// (void)av;
	// int i = -1;
	// int pipe_total = 3;
	// int fd[pipe_total][2];
	// while (++i < pipe_total)
	// {
	// 	if (pipe(fd[i]) < 0)
	// 	{
	// 		return 1; // ! if later pipes fail, close the earlier ones
	// 	}
	// }
	// int pid1 = fork();
	// if (pid1 < 0)
	// 	return 2;
	// if (pid1 == 0)
	// {
	// 	close(fd[0][1]);
	// 	close(fd[1][0]);
	// 	close(fd[2][1]);
	// 	close(fd[2][1]);
	// 	int x;
	// 	if (read(fd[0][0], &x, sizeof(int)) < 0)
	// 		return 3;
	// 	x += 5;
	// 	if (write(fd[1][1], &x, sizeof(int)) < 0)
	// 		return 4;
	// 	close(fd[0][0]);
	// 	close(fd[1][1]);
	// 	return 0;
	// }
	
	// int pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	close(fd[0][0]);
	// 	close(fd[0][1]);
	// 	close(fd[1][1]);
	// 	close(fd[2][0]);
	// 	int x;
	// 	if (read(fd[1][0], &x, sizeof(int)) < 0)
	// 		return 5;
	// 	x += 5;
	// 	if (write(fd[2][1], &x, sizeof(int)) < 0)
	// 		return 6;
	// 	close(fd[2][1]);
	// 	close(fd[1][0]);
	// 	return 0;
	// }

	// close(fd[0][0]);
	// close(fd[1][0]);
	// close(fd[1][1]);
	// close(fd[2][1]);
	// int x = 0;
	// if (write(fd[0][1], &x, sizeof(int)) < 0)
	// 	return 7;
	// if (read(fd[2][0], &x, sizeof(int)) < 0)
	// 	return 8;
	// close(fd[0][1]);
	// close(fd[2][0]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// ft_printf("%d x\n", x);
	// return (0);





/* 	(void)ac;
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
	return (1); */



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
