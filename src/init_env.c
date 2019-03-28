/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:08 by ydemange          #+#    #+#             */
/*   Updated: 2019/03/10 14:40:21 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_player		init_player(char **map)
{
	t_player	player;
	int			x;
	int			y;

	player.dir.x = 1.0;
	player.dir.y = 0.0;
	player.plane.x = 0.0;
	player.plane.y = 2.0 / 3.0;
	y = -1;
	x = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'X')
				break ;
		}
		if (map[y][x] == 'X')
			break ;
	}
	player.x = x + 0.5;
	player.y = y + 0.5;
	return (player);
}

int				init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	if (!(e->win = mlx_new_window(e->mlx, OUTPUT_WIDTH,
					OUTPUT_HEIGHT, "Wolf3D")))
		return (-1);
	if (!(e->img = new_image(e)))
		return (-1);
	if ((get_texture(e) == -1))
		return (-1);
	e->side_tex = -1;
	return (1);
}
