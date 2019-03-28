/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:26:43 by ydemange          #+#    #+#             */
/*   Updated: 2019/03/10 14:37:11 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		is_good(char c)
{
	if (c == '1' || c == '2' || c == '3' || c == '0' ||
		c == '4' || c == '5' || c == 'X')
		return (1);
	return (0);
}

int		check_error(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (!(is_wall(line[0])) || !(is_wall(line[i - 1])))
		return (-1);
	i = -1;
	while (line[++i])
	{
		if (!(is_good(line[i])))
			return (-1);
	}
	return (1);
}

int		check_spawn(char **map)
{
	int i;
	int j;
	int spawn;

	i = -1;
	spawn = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'X')
				spawn = 1;
		}
	}
	return (spawn);
}

int		check_error2(char **map)
{
	int len;
	int i;

	i = 0;
	if (map[0] == NULL)
		return (-1);
	len = ft_strlen(map[0]);
	while (map[++i])
	{
		if (len != (int)ft_strlen(map[i]))
			return (-1);
	}
	len = -1;
	while (map[i - 1][++len])
	{
		if (!(is_wall(map[i - 1][len])))
			return (-1);
	}
	i = -1;
	while (map[0][++i])
	{
		if (!(is_wall(map[0][i])))
			return (-1);
	}
	return (check_spawn(map));
}
