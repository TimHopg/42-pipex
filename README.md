# pipex

A program that simulates the functionality of the UNIX pipe. A 42 School Lisboa project.

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation](#implementation)
  - [Redirects and Pipes](#redirects-and-pipes)
  - [Here Document (heredoc)](#here-document-heredoc)
- [Checker](#checker)
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

Works like input redirect < but allows user to type the text themselves.

## Tips

## Resources
