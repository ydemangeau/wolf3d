/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:02 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/28 17:51:24 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_image			*new_xpm_image(char *xpm, t_env *e)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img =
		mlx_xpm_file_to_image(e->mlx, xpm, &img->width, &img->height)))
		return (NULL);
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
	return (img);
}

t_image			*new_image(t_env *e)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_new_image(e->mlx, OUTPUT_WIDTH, OUTPUT_HEIGHT)))
		return (NULL);
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
	img->width = OUTPUT_WIDTH;
	img->height = OUTPUT_HEIGHT;
	return (img);
}

t_image			*del_image(t_env *e, t_image *img)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(e->mlx, img);
		ft_memdel((void*)&img);
	}
	return (NULL);
}

int				get_texture(t_env *e)
{
	t_image		*img;
	static char	*map[SIZE_TEXTURE_MAP] = {"textures/stone3.xpm",
		"textures/2.xpm", "textures/3.xpm", "textures/4.xpm",
		"textures/5.xpm", "textures/floor.xpm", "textures/cel.xpm", NULL };
	int			i;

	i = -1;
	while (++i < SIZE_TEXTURE_MAP && map[i] != NULL)
	{
		if (!(img = new_xpm_image(map[i], e)))
			return (-1);
		e->texture[i] = img;
	}
	e->floor = e->texture[5];
	e->celling = e->texture[6];
	return (1);
}
