/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:36:21 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/09 17:11:24 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_s(int num)
{
	size_t	len;

	len = 1;
	if (num < 0)
		len++;
	while (num > 9 || num < -9)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = num_s(n);
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (len-- > 0 && str[len] != '-')
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
