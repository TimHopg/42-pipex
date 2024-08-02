/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:31:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/03 00:09:45 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_args.h"
#include "pipex.h"

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
