/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/02 16:06:26 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_split_words{
    int count;
    int in_word;
    int in_quotes;
    char quote_char;
    char *word_start;
} t_split_words;

/*
 * also sets FDs as -1 (not in use)
 */
void	initialise_pipex_struct(int ac, char **av, char **envp, t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(*pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
}

// ! make small function to increase starting index of char** if first str is
// ! empty
// ! test with combination of quotes

static void count_words_util(int *in_word, int *count)
{
	*in_word = 1;
	(*count)++;
}

int count_words_quotes(const char* str)
{
    int count;
    int in_word;
    int in_quotes;

	count = 0;
	in_word = 0;
	in_quotes = 0;
    while (*str)
	{
        if (*str == '\'' || *str == '\"')
		{
            in_quotes = !in_quotes;
            if (!in_word)
				count_words_util(&in_word, &count);
        }
		else if (*str == ' ' && !in_quotes)
            in_word = 0;
		else if (!in_word)
			count_words_util(&in_word, &count);
        str++;
    }
	return (count);
}

#include <stdbool.h>

// ! might need protection if quotes do not match
char** split_words_quotes(const char* str, char **words) {
    bool in_word = false;
    bool in_quotes = false;
    char quote_char = '\0';
    const char* word_start = str;
    
    // Reset variables for second pass
    str = word_start;
    in_word = false;
    in_quotes = false;
    quote_char = '\0';
    int current_word = 0;

    // Second pass: extract words
    while (*str) {
        if (*str == '\'' || *str == '\"') {
            if (!in_quotes) {
                quote_char = *str;
                word_start = str + 1;
                in_quotes = true;
                in_word = true;
            } else if (*str == quote_char) {
                int len = str - word_start;
                words[current_word] = malloc(len + 1);
                if (!words[current_word]) {
                    // Handle allocation failure
                    for (int i = 0; i < current_word; i++) free(words[i]);
                    free(words);
                    return NULL;
                }
                strncpy(words[current_word], word_start, len);
                words[current_word][len] = '\0';
                current_word++;
                in_quotes = false;
                in_word = false;
            }
        } else if (*str == ' ' && !in_quotes) {
            if (in_word) {
                int len = str - word_start;
                words[current_word] = malloc(len + 1);
                if (!words[current_word]) {
                    // Handle allocation failure
                    for (int i = 0; i < current_word; i++) free(words[i]);
                    free(words);
                    return NULL;
                }
                strncpy(words[current_word], word_start, len);
                words[current_word][len] = '\0';
                current_word++;
                in_word = false;
            }
        } else if (!in_word) {
            word_start = str;
            in_word = true;
        }
        str++;
    }

    // Handle the last word if it's not quoted
    if (in_word && !in_quotes) {
        int len = str - word_start;
        words[current_word] = malloc(len + 1);
        if (!words[current_word]) {
            // Handle allocation failure
            for (int i = 0; i < current_word; i++) free(words[i]);
            free(words);
            return NULL;
        }
        strncpy(words[current_word], word_start, len);
        words[current_word][len] = '\0';
        current_word++;
    }

    words[current_word] = NULL;  // NULL terminator

    return words;
}

// ! could skip empty strings if they're a problem in the main function
char **parse_args(char *str)
{
    t_split_words s;
    char **words;

    ft_bzero(&s, sizeof(s));
    str = ft_strtrim(str, " "); // ! malloc
	s.count = count_words_quotes(str);
	if (s.count > 0)
	{
		words = malloc(sizeof(char *) * (s.count + 1));
		// if (words == NULL)
		// 	error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
	}
	else
		exit(1); // ! do what?
	words = split_words_quotes(str, words);
    ft_printf("count: %d\n", s.count);
    return words;
}

// TODO how to find PATH on different systems
// TODO check on linux if outfile creates non existent file
// TODO when creating pipes if later pipes fail, close the earlier ones
// TODO Temp2 for potential errors
// * sometimes appends to outfile?! maybe the way outfile is created?
// 	* Done I think
// ! free args array after exec call? necessary or not?
// TODO separate bonus
// ? is it necessary to free malloc'd memory after an exec call?
// TODO check every failure for leaks or fd leaks
// TODO waitpid()
int	main(int ac, char **av, char **envp)
{
	// t_pipex	pipex;

	// initialise_pipex_struct(ac, av, envp, &pipex);
	// prepare_args(&pipex);  // validates args
	// open_files(&pipex);  // opens file descriptors
	// parse_paths(&pipex); // creates array of paths
	// execute_pipex(&pipex);
	// free_all(&pipex);
	// exit(pipex.last_status);


	char	*cmd;
    char **words;
	(void)ac;
	(void)av;
	(void)envp;
	// cmd = " awk  '{count++} END {print count}' awk";
	cmd = " awk  \"{count++} END {print count}\" awk";
	// cmd = "  awk  '' ''  'a' w 'k' hello '{count++} END {print count}' awk   '";

    words = parse_args(cmd);
    for(int x = 0; words[x]; x++)
        ft_printf(":%s:\n", words[x]);

	// i = count_words_quotes(cmd);
	// ft_printf("%d\n", i);
}
