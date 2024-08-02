/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:55:41 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/02 19:02:57 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_split_words{
    int count;
    int in_word;
    int in_quotes;
    char quote_char;
    char *word_start;
    int curr_word;
    int len;
    char **words; // ! temporary, replace with pipex->args (or whatever)
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

void count_words_quotes(t_split_words *s, char *str)
{
    while (*str)
	{
        if (*str == '\'' || *str == '\"')
		{
            s->in_quotes = !s->in_quotes;
            if (!s->in_word)
            {
                s->in_word = true;
                s->count++;
            }
        }
		else if (*str == ' ' && !s->in_quotes)
            s->in_word = false;
		else if (!s->in_word)
        {
            s->in_word = true;
            s->count++;
        }
        str++;
    }
}

void malloc_word(t_split_words *s, char **words)
{
    words[s->curr_word] = malloc(s->len + 1);
    if (!words[s->curr_word])
    {
        // Handle allocation failure
        for (int i = 0; i < s->curr_word; i++) free(words[i]);
        free(words);
        exit(1); // !
    }
    strncpy(words[s->curr_word], s->word_start, s->len); // ! can't use this
    words[s->curr_word][s->len] = '\0';
}

void if_is_quote(t_split_words *s, char **words, char *str)
{
    if (!s->in_quotes)
    {
        s->quote_char = *str;
        s->word_start = str + 1;
        s->in_quotes = true;
        s->in_word = true;
    }
    else if (*str == s->quote_char)
    {
        s->len = str - s->word_start;
        malloc_word(s, words);
        s->curr_word++;
        s->in_quotes = false;
        s->in_word = false;
    }
}

/*
 * Handles last word if not in quotes.
 */
// void last_word()

// ! might need protection if quotes do not match
char** split_words_quotes(t_split_words *s, char* str, char **words)
{
    s->word_start = str;
    s->quote_char = '\0';
    while (*str)
    {
        if (*str == '\'' || *str == '\"')
            if_is_quote(s, words, str);
        else if (*str == ' ' && !s->in_quotes)
        {
            if (s->in_word)
            {
                s->len = str - s->word_start;
                malloc_word(s, words);
                s->curr_word++;
                s->in_word = false;
            }
        }
        else if (!s->in_word)
        {
            s->word_start = str;
            s->in_word = true;
        }
        str++;
    }

    // Last Word
    if (s->in_word && !s->in_quotes)
    {
        s->len = str - s->word_start;
        malloc_word(s, words);
        s->curr_word++;
    }
    words[s->curr_word] = NULL;  // NULL terminator
    return words;
}

// ! could skip empty strings if they're a problem in the main function
// ! can trim the string of blank space at start?
char **parse_args(char *str)
{
    t_split_words s;
    char **words;

    ft_bzero(&s, sizeof(s));
    str = ft_strtrim(str, " "); // ! malloc
	count_words_quotes(&s, str);
    ft_printf("count: %d\n", s.count);
	if (s.count > 0)
	{
		words = malloc(sizeof(char *) * (s.count + 1));
		// if (words == NULL)
		// 	error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
	}
	else
		exit(1); // ! do what?
    ft_bzero(&s, sizeof(s));
	words = split_words_quotes(&s, str, words);
    free(str);
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

