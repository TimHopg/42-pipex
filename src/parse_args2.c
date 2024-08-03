/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:28:35 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/03 20:11:11 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_args.h"
#include "pipex.h"

// ! make small function to increase starting index of char** if first str is
// ! empty
// ! test with combination of quotes
void	malloc_word(t_pipex *p, t_split_words *s)
{
	p->args[s->curr_word] = malloc(s->len + 1);
	if (p->args[s->curr_word] == NULL)
	// ! works because largest index must be NULL?
	{
		free(s->str);
		error_handling(NULL, ERR_MALLOC, p, EXIT_FAILURE); // ! test
	}
	ft_strlcpy(p->args[s->curr_word], s->word_start, s->len + 1);
	p->args[s->curr_word][s->len] = '\0';
}

void	if_is_quote(t_pipex *p, t_split_words *s, char *str)
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
		malloc_word(p, s);
		s->curr_word++;
		s->in_quotes = false;
		s->in_word = false;
	}
}

/*
 * Handles last word if not in quotes.
 */
static void	last_word(t_pipex *p, t_split_words *s, char *str)
{
	if (s->in_word && !s->in_quotes)
	{
		s->len = str - s->word_start;
		malloc_word(p, s);
		s->curr_word++;
	}
}

// ! might need protection if quotes do not match
void	split_words_quotes(t_pipex *p, t_split_words *s, char *str)
{
	s->word_start = str;
	s->quote_char = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			if_is_quote(p, s, str);
		else if (*str == ' ' && !s->in_quotes)
		{
			if (s->in_word)
			{
				s->len = str - s->word_start;
				malloc_word(p, s);
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
	last_word(p, s, str);
}

// ! could skip empty strings if they're a problem in the main function
// ! can trim the string of blank space at start?
void	parse_args(t_pipex *pipex, char *str)
{
	t_split_words	s;

	ft_bzero(&s, sizeof(s));
	str = ft_strtrim(str, " "); // ! malloc
	if (str == NULL)
		error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE);
	count_words_quotes(&s, str);
	if (s.count > 0)
	{
		pipex->args = malloc(sizeof(char *) * (s.count + 1));
		if (pipex->args == NULL)
		{
			free(str);
			error_handling(NULL, ERR_MALLOC, pipex, EXIT_FAILURE); // ! TEST
		}
	}
	else
		exit(1); // ! do what?
	ft_bzero(&s, sizeof(s));
	s.str = str;
	split_words_quotes(pipex, &s, str);
	pipex->args[s.curr_word] = NULL;
	free(str);
}
