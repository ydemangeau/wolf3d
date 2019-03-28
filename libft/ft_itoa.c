/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:40:58 by ydemange          #+#    #+#             */
/*   Updated: 2018/11/23 16:42:57 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*result;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = count(n);
	if (!(result = (char *)malloc(sizeof(char) * i + 2)))
		return (NULL);
	result[i + 1] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	while (n >= 10)
	{
		result[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	result[i] = n + 48;
	return (result);
}
