#!/bin/bash

# Name of your large text file
LARGE_FILE="rndstring.txt"

# Your pipex command
PIPEX_CMD="./pipex here_doc EOF cat cat outfile"

# Feed the content of the large file to pipex
cat $LARGE_FILE | $PIPEX_CMD
echo "EOF"
