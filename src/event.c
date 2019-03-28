/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:26:51 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/27 19:26:53 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			get_pos_value(char **map, int x, int y)
{
	if (x < 0 || y < 0 || x > OUTPUT_WIDTH - 1 || y > OUTPUT_HEIGHT - 1)
		return (0);
	return (is_available(map[y][x]));
}

void		rotate(t_vector *vector, double angle)
{
	double	x;
	double	c;
	double	s;

	x = vector->x;
	c = cos(angle);
	s = sin(angle);
	vector->x = vector->x * c - vector->y * s;
	vector->y = x * s + vector->y * c;
}

void		rotate_player(t_player *player, int key)
{
	double	angle;

	angle = (key == KEY_RIGHT ? 5.0 : -5.0) / 180.0 * M_PI;
	rotate(&player->dir, angle);
	rotate(&player->plane, angle);
}

void		move_player(t_env *e, int key)
{
	double	distance;
	int		x;
	int		y;

	distance = key == KEY_UP ? 0.1 : -0.1;
	x = e->player.x + distance * e->player.dir.x;
	y = e->player.y + distance * e->player.dir.y;
	if (get_pos_value(e->map, x, e->player.y))
		e->player.x += distance * e->player.dir.x;
	if (get_pos_value(e->map, e->player.x, y))
		e->player.y += distance * e->player.dir.y;
}

int			key_event(int key, t_env *e)
{
	if (key == KEY_ESC)
	{
		del(e->map);
		ft_memdel((void**)&e);
		exit(0);
	}
	else if (key == KEY_UP || key == KEY_DOWN)
		move_player(e, key);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		rotate_player(&e->player, key);
	else if (key == KEY_A)
		e->side_tex = (e->side_tex < 0 ? 1 : -1);
	raycasting(e);
	return (0);
}
