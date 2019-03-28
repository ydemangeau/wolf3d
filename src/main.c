/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:27:15 by ydemange          #+#    #+#             */
/*   Updated: 2019/02/28 17:03:46 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			error(t_env *e, char *reason)
{
	(void)e;
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}

int			close_prog(t_env *e)
{
	(void)e;
	exit(EXIT_SUCCESS);
	return (0);
}

int			main(int argc, char **argv)
{
	t_env	*e;

	if (!(e = (t_env *)ft_memalloc(sizeof(t_env))))
		return (error(e, "error : environment init fail"));
	if (argc != 2)
		return (error(e, "error : missing file operand"));
	if ((e->fd = open(argv[1], O_RDONLY)) == -1)
		return (error(e, "error : bad file descriptor"));
	if ((e->map = get_map(e->fd)) == NULL)
		return (error(e, "error : bad map format"));
	if ((init_mlx(e)) == -1)
		return (error(e, "image not load"));
	e->player = init_player(e->map);
	raycasting(e);
	mlx_hook(e->win, 2, 1L << 0, key_event, e);
	mlx_hook(e->win, 17, 1L << 0, close_prog, e);
	mlx_loop(e->mlx);
	return (0);
}
