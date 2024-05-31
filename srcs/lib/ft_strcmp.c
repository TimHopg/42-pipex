/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:51:33 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 12:21:37 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	c = 0;
	while (s1[c] == s2[c] && (s1[c] && s2[c]) && c < n - 1)
		c++;
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}
