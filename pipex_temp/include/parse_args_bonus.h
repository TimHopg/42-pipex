/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:09:23 by thopgood          #+#    #+#             */
/*   Updated: 2024/08/14 17:23:07 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARGS_BONUS_H
# define PARSE_ARGS_BONUS_H

typedef struct s_split_words
{
	int		count;
	int		in_word;
	int		in_quotes;
	char	quote_char;
	char	*word_start;
	int		curr_word;
	int		len;
	char	*str; // ! malloc
}			t_split_words;

void		count_words_quotes(t_split_words *s, char *str);

#endif