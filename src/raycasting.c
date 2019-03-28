/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:39 by ydemange          #+#    #+#             */
/*   Updated: 2019/03/01 19:39:28 by fdrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_column(t_env *e, t_ray *ray, int x)
{
	int			y;

	if ((ray->start = -(ray->hauteur) / 2 + OUTPUT_HEIGHT / 2) < 0)
		ray->start = 0;
	if ((ray->end = ray->hauteur / 2 + OUTPUT_HEIGHT / 2) >= OUTPUT_HEIGHT)
		ray->end = OUTPUT_HEIGHT - 1;
	ray->tex = e->texture[ray->hit - 1];
	y = ray->start;
	while (++y < ray->end)
	{
		if (e->side_tex == 1)
			ray->tex = get_side_tex(e, ray);
		ray->tex_x = (int)(ray->wallx * ray->tex->width);
		ray->tex_y = ((y - OUTPUT_HEIGHT * 0.5 + ray->hauteur * 0.5)
			* ray->tex->height) / ray->hauteur;
		set_tex_pixel(e, ray, x, y);
	}
	draw_floor(e, ray, x, y);
}

void		cast(t_env *e, t_ray *ray)
{
	char	hit;

	hit = 0;
	while (is_wall(hit) == 0)
	{
		if (ray->sidex < ray->sidey)
		{
			ray->sidex += ray->dx;
			ray->mx += ray->stepx;
			ray->hit_side = 0;
		}
		else
		{
			ray->sidey += ray->dy;
			ray->my += ray->stepy;
			ray->hit_side = 1;
		}
		hit = e->map[ray->my][ray->mx];
	}
	ray->hit = hit - 48;
	if (ray->hit_side == 0)
		ray->distance = (ray->mx - e->player.x + (1 - ray->stepx) / 2) / ray->x;
	else
		ray->distance = (ray->my - e->player.y + (1 - ray->stepy) / 2)
			/ ray->y;
}

void		init_ray(t_ray *ray, t_env *e, int x)
{
	ray->mx = (int)e->player.x;
	ray->my = (int)e->player.y;
	ray->cam = 2.0 * x / OUTPUT_WIDTH - 1;
	ray->x = e->player.dir.x + e->player.plane.x * ray->cam;
	ray->y = e->player.dir.y + e->player.plane.y * ray->cam;
	ray->dx = sqrt(1 + (ray->y * ray->y) / (ray->x * ray->x));
	ray->dy = sqrt(1 + (ray->x * ray->x) / (ray->y * ray->y));
	ray->stepx = (ray->x < 0 ? -1 : 1);
	ray->stepy = (ray->y < 0 ? -1 : 1);
	ray->sidex = (ray->x < 0 ? e->player.x - ray->mx :
			ray->mx - e->player.x + 1) * ray->dx;
	ray->sidey = (ray->y < 0 ? e->player.y - ray->my :
			ray->my - e->player.y + 1) * ray->dy;
	ray->distance = -1;
	ray->hit = 0;
	ray->hit_side = -1;
}

void		raycasting(t_env *e)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < OUTPUT_WIDTH)
	{
		init_ray(&ray, e, x);
		cast(e, &ray);
		ray.wallx = (ray.hit_side ? e->player.x + ray.distance * ray.x :
				e->player.y + ray.distance * ray.y);
		ray.wallx -= floor((ray.wallx));
		ray.hauteur = (int)(OUTPUT_HEIGHT / ray.distance);
		draw_column(e, &ray, x);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
}
