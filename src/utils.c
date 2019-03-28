/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:26:02 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/28 17:04:08 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		is_wall(char c)
{
	if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5')
		return (1);
	return (0);
}

int		is_available(char c)
{
	if (c == '0' || c == 'X')
		return (1);
	return (0);
}
