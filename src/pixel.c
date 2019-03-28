/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:34 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/27 19:27:35 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		put_pixel_to_image(t_image *img, int x, int y, int color)
{
	if (x < OUTPUT_WIDTH && y < OUTPUT_HEIGHT)
		ft_memcpy(img->data + 4 * OUTPUT_WIDTH * y + x * 4,
		&color, sizeof(int));
}

int			get_tex_pixel(t_image *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return (0);
	return ((int)*(int *)(image->data + 4 * image->width * y + x * 4));
}

void		set_tex_pixel(t_env *e, t_ray *ray, int x, int y)
{
	int		color;

	color = mlx_get_color_value(e->mlx,
		get_tex_pixel(ray->tex, ray->tex_x, ray->tex_y));
	put_pixel_to_image(e->img, x, y, color);
}

t_image		*get_side_tex(t_env *e, t_ray *ray)
{
	if (ray->hit_side == 1)
	{
		if ((ray->stepx == -1 && ray->stepy == -1) ||
		(ray->stepx == 1 && ray->stepy == -1))
			return (e->texture[0]);
		if ((ray->stepx == -1 && ray->stepy == 1) ||
		(ray->stepx == 1 && ray->stepy == 1))
			return (e->texture[1]);
	}
	if ((ray->stepx == -1 && ray->stepy == -1) ||
	(ray->stepx == -1 && ray->stepy == 1))
		return (e->texture[2]);
	return (e->texture[3]);
}
