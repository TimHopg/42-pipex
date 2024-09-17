#!/bin/bash

# Name of your large text file
LARGE_FILE="rndstring.txt"

# Your pipex command
(cat $LARGE_FILE && echo "EOF") | (cat -b | cat -b >> outfile) 
