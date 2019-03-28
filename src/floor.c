/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:26:56 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/27 19:26:58 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vector		cast_floor(t_ray *ray)
{
	t_vector	floor;

	if (ray->hit_side == 0 && ray->x > 0)
	{
		floor.x = ray->mx;
		floor.y = ray->my + ray->wallx;
	}
	else if (ray->hit_side == 0 && ray->x < 0)
	{
		floor.x = ray->mx + 1.0;
		floor.y = ray->my + ray->wallx;
	}
	else if (ray->hit_side == 1 && ray->y > 0)
	{
		floor.x = ray->mx + ray->wallx;
		floor.y = ray->my;
	}
	else
	{
		floor.x = ray->mx + ray->wallx;
		floor.y = ray->my + 1.0;
	}
	return (floor);
}

void			draw_floor(t_env *e, t_ray *ray, int x, int y)
{
	t_vector	floor;
	double		current;
	double		weight;

	floor = cast_floor(ray);
	while (y < OUTPUT_HEIGHT)
	{
		ray->tex = e->floor;
		current = OUTPUT_HEIGHT / (2.0 * y - OUTPUT_HEIGHT);
		weight = current / ray->distance;
		ray->tex_x = (int)((weight * floor.x + (1.0 - weight) * e->player.x) *
			e->floor->width) % e->floor->width;
		ray->tex_y = (int)((weight * floor.y + (1.0 - weight) * e->player.y) *
			e->floor->height) % e->floor->height;
		set_tex_pixel(e, ray, x, y);
		ray->tex = e->celling;
		ray->tex_x = (int)((weight * floor.x + (1.0 - weight) *
			e->player.x) * e->celling->width) % e->celling->width;
		ray->tex_y = (int)((weight * floor.y + (1.0 - weight) *
			e->player.y) * e->celling->height) % e->celling->height;
		set_tex_pixel(e, ray, x, OUTPUT_HEIGHT - y);
		y++;
	}
}
