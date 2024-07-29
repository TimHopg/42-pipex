/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/29 21:07:54 by thopgood         ###   ########.fr       */
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

/* void execute2(t_pipex *p, int ac, char **av, char ** envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	int prev_fd;

	prev_fd = p->infile_fd;
	int pipe_fd[2];

	for (int i = 2; i < ac - 1; i++)
	{
		if (i < ac - 2)
		{
			pipe(pipe_fd);
		}
		else
			pipe_fd[1] = p->outfile_fd;

		pid_t pid = fork(); // ! try putting outside for loop;
		if (pid == 0)
		{
			if (i > 2)
				close(prev_fd);
			close(pipe_fd[0]);
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (pipe_fd[1] != STDOUT_FILENO)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			exec_command(p, i);
		}
		else
		{
			wait(NULL);
			close(prev_fd);
			if (i < ac - 2)
				close (pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
	}
} */

/* void execute(char **av, char **envp, t_pipex *p) // this works simple
{
	pid_t pid1;
	pid_t pid2;
	int pipefd[2];

	pipe(pipefd);
	pid1 = fork();

	// while (p->i < p->pipe_total) // iterate until last command
	// {
	// 	if (p->i + p->is_here_doc )
	// }

	if (pid1 == 0)
	{
		dup2(p->infile_fd, STDIN_FILENO);
		close(p->infile_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]); // close unused read end
		close(pipefd[1]); // close original write end
		exec_command(p, av, envp, 2);
		errno_handling("1", p);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(p->outfile_fd, STDOUT_FILENO);
		close(p->outfile_fd);
		exec_command(p, av, envp, 3);
		errno_handling("2", p);
	}

	// parent process
	close(pipefd[0]);
	close(pipefd[1]);

	close(p->infile_fd);
	close(p->outfile_fd);

	wait(NULL); // use waitpid(-1 status etc)
	wait(NULL);
} */

void dup2_both(int read_fd, int write_fd)
{
	if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
	if (write_fd != STDOUT_FILENO)
	{
		dup2(write_fd, STDOUT_FILENO);
		close(write_fd);
	}
}

/* void process_fork(char **av, char **envp, t_pipex *p)
{
	(void)av;
	(void)envp;
	if (p->pid == 0)
	{
		ft_printf("check\n");
		if (p->i > 1)
			close(p->prevfd);
		dup2_both(p->prevfd, p->pipefd[1]);
		exec_command(p, p->i - 1);
	}
	else
	{
		wait(NULL); // waitpid
		close(p->prevfd);
		if (p->i <= p->pipe_total)
			close(p->pipefd[1]);
		p->prevfd = p->pipefd[0];
	}
} */

// void execute(int ac, char **av, char **envp, t_pipex *p)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)envp;
// 	p->prevfd = p->infile_fd;
// 	while (++p->i <= p->cmd_total) // iterate until and incl last command
// 	{
// 		if (p->i <= p->pipe_total) // create a pipe only when required
// 		{
// 			pipe(p->pipefd); // ! erro
// 		}
// 		else // on last iteration
// 		{
// 			ft_printf("i: %d\n", p->i);
// 			p->pipefd[1] = p->outfile_fd;
// 		}

// 		p->pid = fork();
// 		if (p->pid < 0)
// 			errno_handling(NULL, p);

// 		process_fork(av, envp, p);
		
// 		/* if (p->i == 2 + p->is_here_doc) // first iteration
// 			dup2_both(p->infile_fd, pipe */
// 	}

// 	// if (pid1 == 0)
// 	// {
// 	// 	dup2(p->infile_fd, STDIN_FILENO);
// 	// 	close(p->infile_fd);
// 	// 	dup2(pipefd[1], STDOUT_FILENO);
// 	// 	close(pipefd[0]); // close unused read end
// 	// 	close(pipefd[1]); // close original write end
// 	// 	exec_command(p, av, envp, 2);
// 	// 	errno_handling("1", p);
// 	// }
// 	// pid2 = fork();
// 	// if (pid2 == 0)
// 	// {
// 	// 	dup2(pipefd[0], STDIN_FILENO);
// 	// 	close(pipefd[0]);
// 	// 	close(pipefd[1]);
// 	// 	dup2(p->outfile_fd, STDOUT_FILENO);
// 	// 	close(p->outfile_fd);
// 	// 	exec_command(p, av, envp, 3);
// 	// 	errno_handling("2", p);
// 	// }

// 	// // parent process
// 	// close(pipefd[0]);
// 	// close(pipefd[1]);

// 	// close(p->infile_fd);
// 	// close(p->outfile_fd);

// 	// wait(NULL); // use waitpid(-1 status etc)
// 	// wait(NULL);
// }

/*
 * Splits args from the arg_numth argument vector. Cycles through available
 * paths appending the cmd name to each path name until a successful match is
 * found then executes using execve(). 
 ! If no successful path is found?
 ! change from arg_num to p->i and test
 */
void execute_command(t_pipex *pipex, int arg_num)
{
	int i;

	i = -1;
	char *full_path;
	// printf("args%s\n", pipex->args[arg_num]);
	// ft_putstr_fd("tim\n", 2);
	// dprintf(2, "check\n");
	// ft_putstr_fd("check\n", 2);
	pipex->args = ft_split(pipex->av[arg_num], ' '); // ! malloc
	while (pipex->paths[++i])
	{
		full_path = ft_strjoin(pipex->paths[i], pipex->args[0]); // ! malloc
		if (access(full_path, X_OK) == 0)
			{
				// ft_printf("%s\n", full_path);
				execve(full_path, pipex->args, pipex->envp);
				free(full_path);
				errno_handling(NULL, pipex);
			}
		free(full_path);
	}
	// ! command not found function goes here?
}

void fork_and_run(t_pipex *p)
{
	int prevfd;
	int pipefd[2];

	prevfd = p->infile_fd;
	// ft_printf("i:%d pipe_total:%d\n", p->i, p->pipe_total);
	while (++p->i < p->cmd_total)
	{
		pipe(pipefd);
		pid_t pid = fork();

		if (pid == 0)
		{
			close(pipefd[0]);

			dup2(prevfd, STDIN_FILENO);
			if (prevfd != STDIN_FILENO) // this could be STDIN if there was no infile
				close(prevfd);
			
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]); // needs no conditional since it's always a new fd (> 2)
			execute_command(p, p->i + 1);
			exit(1); // !
		}

		close(pipefd[1]);
		if (prevfd != STDIN_FILENO)
			close(prevfd);
		prevfd = pipefd[0];
	}

	//last command
	pid_t pid = fork();

	if (pid == 0)
	{
		dup2(prevfd, STDIN_FILENO);
		if (prevfd != STDIN_FILENO)
			close(prevfd);
		
		dup2(p->outfile_fd, STDOUT_FILENO);
		close(p->outfile_fd);

		execute_command(p, p->i + 1);
		exit(1); // !
	}

	if (prevfd != STDIN_FILENO)
			close(prevfd);

	while (wait(NULL) > 0);

}


void initialise_pipex_struct(int ac, char **av, char **envp, t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(*pipex)); // initialises struct
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
}

// TODO how to find PATH on different systems
// TODO check on linux if outfile creates non existent file
// TODO when creating pipes if later pipes fail, close the earlier ones
// TODO when closing FDs, set FD to -1.
// TODO does it overwrite file if it exists
// ? don't quit when one pipe fails so the following ones still produce an
// ?	output like piping to wc from a file that doesnt exist ( probably not a good idea)
// ! You can create a pipe before each process. or a circular buffer of two 
// !	pipes and reuse the same FDs
// ! free args array after exec call? necessary or not?
// ! having envp in the struct might permanently change the pointer in parse paths
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	(void)ac;
	(void)av;
	(void)envp;
	// ft_bzero(&pipex, sizeof(pipex)); // initialises struct
	initialise_pipex_struct(ac, av, envp, &pipex);
	parse_args(&pipex); // validates args
	open_files(&pipex); // opens file descriptors
	parse_paths(&pipex); // creates array of paths

	fork_and_run(&pipex);

	// execute_command(&pipex, 2);

	// execute(ac, av, envp, &pipex);
	// execute2(&pipex, ac, av, envp);
	

	// run_pipex(av, envp, &pipex);
	
	// exec_command(&pipex, av, envp, 2);
	// free_char_array(pipex.args); // ! i think this is necessary since it is not freed
	// // ! before or maybe the exiting of a process clears the memory?


	// run_pipex(ac, av, &pipex, envp);
	// errno_handling(NULL, &pipex);

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
