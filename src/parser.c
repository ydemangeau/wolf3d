/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:23 by ydemange          #+#    #+#             */
/*   Updated: 2019/03/10 14:35:12 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char		**del(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
		ft_memdel((void**)&map[i++]);
	free(map);
	return (NULL);
}

char		**alloc(char **map, char *line, int i)
{
	char	**nmap;
	int		a;

	a = -1;
	if (!(nmap = ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (++a != i)
		nmap[a] = ft_strdup(map[a]);
	nmap[i] = ft_strdup(line);
	nmap[i + 1] = NULL;
	map = del(map);
	return (nmap);
}

char		**get_map(int fd)
{
	char	**map;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	if (!(map = ft_memalloc(sizeof(int *) * 1)))
		return (NULL);
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (check_error(line) == -1)
			return (del(map));
		map = alloc(map, line, i);
		free(line);
		i++;
	}
	if (ret == -1)
		return (del(map));
	if (check_error2(map) == -1)
		return (del(map));
	return (map);
}
