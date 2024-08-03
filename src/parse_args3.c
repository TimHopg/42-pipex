/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:31:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/03 21:01:35 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_args.h"
#include "pipex.h"

/*
 * Counts words and considers anything between quotes as one word (arg)
 */
void	count_words_quotes(t_split_words *s, char *str)
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
