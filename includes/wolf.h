/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrias <fdrias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:03:28 by fdrias            #+#    #+#             */
/*   Updated: 2019/03/01 17:03:33 by fdrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdint.h>
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define OUTPUT_WIDTH  720
# define OUTPUT_HEIGHT 480
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_A 0
# define SIZE_TEXTURE_MAP 8

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_player
{
	double			x;
	double			y;
	t_vector		dir;
	t_vector		plane;
}					t_player;

typedef struct		s_image
{
	void			*img;
	char			*data;
	int				endian;
	int				sl;
	int				bpp;
	int				height;
	int				width;
}					t_image;

typedef struct		s_ray
{
	int				mx;
	int				my;
	double			x;
	double			y;
	double			dx;
	double			dy;
	double			distance;
	double			cam;
	double			stepx;
	double			stepy;
	double			sidex;
	double			sidey;
	int				hit;
	int				hit_side;
	double			wallx;
	double			hauteur;
	int				tex_x;
	int				tex_y;
	int				start;
	int				end;
	t_image			*tex;
}					t_ray;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				fd;
	char			**map;
	int				side_tex;
	t_player		player;
	t_image			*img;
	t_image			*texture[SIZE_TEXTURE_MAP];
	t_image			*floor;
	t_image			*celling;
}					t_env;

int					get_tex_pixel(t_image *image, int x, int y);
void				put_pixel_to_image(t_image *img, int x, int y, int color);
char				**get_map(int fd);
int					is_available(char c);
int					is_wall(char c);
int					check_error(char *line);
int					check_error2(char **map);
int					get_texture(t_env *e);
int					init_mlx(t_env *e);
int					key_event(int key, t_env *e);
void				draw_floor(t_env *e, t_ray *ray, int x, int y);
void				raycasting(t_env *e);
void				set_tex_pixel(t_env *e, t_ray *ray, int x, int y);
t_image				*get_side_tex(t_env *e, t_ray *ray);
t_image				*new_xpm_image(char *xpm, t_env *e);
t_image				*new_image(t_env *e);
t_player			init_player(char **map);
char				**del(char **map);

#endif
