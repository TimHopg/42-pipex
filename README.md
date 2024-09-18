# pipex

A program that simulates the functionality of the UNIX pipe. A 42 School Lisboa project.

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation](#implementation)
  - [Redirects and Pipes](#redirects-and-pipes)
  - [Here Document (heredoc)](#here-document-heredoc)
  - [Functions](#functions)
    - [`access()`](#access)
    - [`dup2()`](#dup2)
    - [`pipe()`](#pipe)
    - [`fork()`](#fork)
    - [`waitpid()`](#waitpid)
    - [`wait()`](#wait)
    - [`execve()`](#execve)
    - [`unlink()`](#unlink)
- [envp](#envp)
- [Orphan Processes](#orphan-processes)
- [SIGPIPE](#sigpipe)
- [Exit Statuses](#exit-statuses)
- [PATH](#path)
- [Tips](#tips)
- [Resources](#resources)

## Introduction

A 42 School Lisboa project to create `pipe` and `heredoc` functionality on the command line. Written in C.

The program will implement `<`, `>` and `>>` redirects as well as `<<` (heredoc) and `|` (multiple pipes).

## Installation

Git clone the repository:

```shell
https://github.com/TimHopg/42-pipex.git
```

Run `make` from within the directory to create the program `pipex`.

`make clean` removes object files.

`make fclean` removes program and object files.

## Usage

```shell
./pipex [file1] [cmd1] [cmd2] ... [file2]
```

Will behave like:  
`< file1 cmd1 | cmd 2 | ... > file2`

Each of the commands can contain their relevant flags but must be contained in a single argument string:  
`"ls -l"`

```shell
./pipex "here_doc" [DELIMITER] [cmd2] ... [file2]
```

Will behave like:  
`cm1d << DELIMITER | cmd2 >> file`

When the first argument is exactly "here_doc", the second argument will act as the delimiting string to signal `EOD` (end of document/data). In this instance the output will be appended to the final file instead of overwritten (`>>`).

## Implementation

### File Descriptors

In Unix-like operating systems, everything is a file, including standard input (`stdin`), standard output (`stdout`), and standard error (`stderr`). Understanding file descriptors and how they're used for I/O operations is integral to the project.

### Redirects and Pipes

`<` - input redirect. Redirects a file descriptor to `STDIN (fd0)`.
`>` - output redirect. Sends `STDOUT (fd1)` of a command to a specified file/fd.

On the command line this can be written as `< infile cmd1` which can appear a bit confusing and might be easier to understand as `cmd1 < infile`. But for the sake of the project, it makes sense for the files to be at the beginning and end of the args.  
`< file grep a1` = `grep a1 < file`

`cmd > output.txt 2>&1` - redirects output of `STDOUT` and `STDERR` to the same file.

`|` - pipe redirects output of one command to the input of the next command. Pipes connect processes to eachother. Redirects connect processes with files/file descriptors.

`cmd1 < input.txt | cmd2 > output.txt`  
Separate the commands by the pipe and work out what each side is doing. `input.txt` is being sent to the input of `cmd1` which is then being piped to the input of `cmd2` and `cmd2`'s output is being sent to `output.txt`.

### Here Document (heredoc)

Allows the user to specify multiline input directly on the command line or script. Everything until the delimiter is inputed as text (usually `EOF`).

```SHELL
cat << EOF
line 1
line 2
EOF
```

Works like input redirect < but allows user to type the text themselves. `here_doc` is the only command that is run sequentially. Everything else is run in parallel/concurrently.

### Functions

#### `access()`

`int access(constant char *pathname, int mode)`

`access()` checks whether the program can access pathname. `mode` determines which checks are performed.

- `F_OK` checks for file existence

The following check for existence plus:

- `R_OK` - read permissions
- `W_OK` - write permissions
- `X_OK` - execute permissions

They can be separate by bitwise or operators. `access()` returns `0` if successful or `-1` if an error occurred. `errno` is set.

#### `dup2()`

`int dup2(int oldfd, int newfd);`

`dup2()` makes `newfd` a copy of `oldfd`, closing `newfd` first if necessary.

- If `oldfd` is not a valid fd, the call fails and `newfd` is **NOT** closed
- If `oldfd` is valid and `newfd` has the same value, `dup2()` does nothing and returns `newfd`.

They now can be used interchangeably and share the same offset and file status flags. Any changes made to one will affect the other.

So if you pass `STDOUT_FILENO`(standard out file number) as `newfd` you can reroute another file descriptor to the standard out.  
*`dup2()` doesn't just move a file descriptor, it creates another one so you must close the previous `fd` after calling it.*

#### pipe()

`int pipe(int pipefd[2]);`

`pipe()` creates a unidirectional data channel that can be used for interprocess communication. The array `pipefd` returns two file descriptors referring to the ends of the pipe. `pipefd[0]` is the read end of the pipe and `pipefd[1]` is the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe

On success, `0` is returned. On error, `-1` is returned, and `errno` is set.

#### fork()

`pid_t fork(void);`

`fork()` creates a new process by duplicating the calling process. The new process, referred to as the `child`, is an exact duplicate of the calling process, referred to as the `parent`, except for in the following [cases](https://linux.die.net/man/2/fork).

#### waitpid()

`pid_t waitpid(pid_t pid, int *status, int options);`

The `waitpid()` system call suspends execution of the calling process until a child specified by *pid* argument has changed state. By default, `waitpid()` waits only for terminated children.

``` C
int pid;
pid = fork();
waitpid(pid);
```

#### wait()

`pid_t wait(int *status);`

The `wait()` system call suspends execution of the calling process until one of its children terminates.

```C
// waiting for multiple children
int main(void){
  int status;

    while (n > 0)
    {
        wait(&status);
        n--;
    }}
```

#### execve()

`int execve(const char *filename, char *const argv[], char *const envp[]);`

`execve()` executes the program pointed to by `filename`. This is the path of the program like `ping`. Could be `usr/bin/ping`.

`argv` argument is `{"program_name", "flag/argument1", "flag/argument2", NULL}`
The argv string must be NULL terminated.

`execve()` does not return on success, the calling process is **replaced** by the executed `filename` but the PID remains the same.

The whole process is replaced by the program so nothing can be run in this process afterwards. Anything afterwards will only be run if an error occurs with `execve()` i.e. memory management can occur.

`envp` will be the environment variables that the new process will have access to. You can send a modified `envp` list to give it access to a specific library path for instance.

*For error handling, you can use the same process without conditionals since any code after `execve()` will not run if `execve()` is successful.*

#### unlink()

`int unlink(const char *pathname);`

`unlink()` deletes a pathname from the file system. If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to it is closed.

On success, `0` is returned. On error, `-1` is returned, and `errno` is set appropriately.

### envp

Environment Pointer. Environment variables, the third argument sent to main, contains the system variables that can be used by the program. `PATH=` is one of these variables which contains the system's paths to binaries (where the cmds may be stored).

```SHELL
OLD_PATH=$PATH
unset PATH
# test pipex here
export PATH=$OLD_PATH
```

When no [PATH](#path) is set or when there is no environment, on Linux systems, the default of `usr/bin` and `bin` are used.

### Orphan Processes

Every process has an ID (a number unique to that process).

To avoid zombie/orphan processes, it's important for all parent processes to `wait()` until the child processes have terminated.
When using multiple forks, processes may have more than one child process. So `wait(NULL)` by itself may not work correctly. Instead use:

```C
while (wait(NULL) != -1 && errno != ECHILD)
  (void)0;
```

### SIGPIPE

`yes | head -n 5` - The `yes` command continuously outputs "yes" until it is killed. After head has read its 5 lines it closes the input stream. The next time `yes` tries to write it instead receives a `SIGPIPE` signal which is how it knows when to terminate.

### Exit Statuses

In a pipeline, the exit status will reflect the status of the last pipe in the line. So even if a file does not exist, if the last cmd is successful, the EXIT_STATUS will be `0`.  
You can determine the exit status of your command with the command
`echo $?`. Some exit statuses don't match with the POSIX systems used by C so check the CLI exit statuses carefully.

### PATH

When the environment is not set `env -i` the default of `usr/bin:/bin` is used as the directory to look for programs. This is to ensure system programs can still be found when the path is not set.

## Tips

- `>` redirect. When file does not exist, it is created but also truncated.  
`open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);`  
The octal `0644` represents `rw- r-- r--` (user/group/other). Don't be lazy and use `0777` (why would you grant execute permissions?).
- `>>` append redirect.  
`open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);`  
Appends to file instead of deleting and starting again.
- Edge cases: check for the existence of files, permissions, handle cases where commands are missing, where the environment is not set etc.
- You need `get_next_line` for `here_doc`.
- commands in the same directory must only be executed if preceded by `./`
- check for non-executable cmds, should return err code `126`
- try here_doc with empty string
- check pipex can execute a command in the same directory AND subdirectories
- delimeter can be `""`
- `./pipex here_doc " " "cat -b" " " outfile` - this should give the here_doc prompt and then return, command not found

`dup2(fd[1], STDOUT_FILENO)` - reroutes the standard out to file descriptor 1 which is the write end of the pipe. `fd[0]` = read, `fd[1]` = write.

You will need one fork per `cmd`.  
forks = number of `cmd`'s

And a pipe to go between each pair of commands?  
Not necessarily. When forking child processes, most of the memory incl. variables is copied. So if you created 10 pipes and then fork 10 child processes you can quickly be pretty wasteful with resources.

It is possible (and recommended) to instead reuse pipes in a loop. This way you only need 1 and a half pipes open at once.

In the child process loop, the last `cmd` will need a fork but will not need a pipe.

## Resources

- [The Fork System Call](https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html)
- [Pipes, Forks and Dupes](https://www.rozmichelle.com/pipes-forks-dups/)
- [LSOF](https://ioflood.com/blog/lsof-linux-command/)
- [Medium: CS Notes](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
- [Reactive](https://reactive.so/post/42-a-comprehensive-guide-to-pipex/)
- [Gitbook: 42](https://42-cursus.gitbook.io/guide/rank-02/pipex)
