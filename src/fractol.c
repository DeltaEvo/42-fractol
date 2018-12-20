/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 09:13:46 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/20 11:48:44 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "ft/mlx.h"
#include <stdlib.h>

static int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	float	oscale;

	(void)x;
	(void)y;
	if (button == 5 || button == 4)
	{
		oscale = button == 5 ? 1.1 : 0.9;
		fractol->scale *= oscale;
	}
	return (render(fractol));
}

static int	key_hook2(int key, t_fractol *fractol)
{
	if (key == X_KEY_UP)
		fractol->y -= 100 / fractol->scale;
	else if (key == X_KEY_DOWN)
		fractol->y += 100 / fractol->scale;
	else if (key == X_KEY_LEFT)
		fractol->x -= 100 / fractol->scale;
	else if (key == X_KEY_RIGHT)
		fractol->x += 100 / fractol->scale;
	else if (key == X_KEY_PLUS)
		fractol->max_iter += 25;
	else if (key == X_KEY_MINUS && fractol->max_iter >= 25)
		fractol->max_iter -= 25;
	else if (key == X_KEY_ESC)
	{
		mlx_destroy_image(fractol->mlx, fractol->ximg);
		mlx_destroy_window(fractol->mlx, fractol->win);
		exit(0);
	}
	else
		return (0);
	return (1);
}

static int	key_hook(int key, t_fractol *fractol)
{
	if (!key_hook2(key, fractol))
	{
		if (key == X_KEY_M)
			fractol->current = g_fractals;
		else if (key == X_KEY_J)
			fractol->current = g_fractals + 1;
		else if (key == X_KEY_L)
			fractol->current = g_fractals + 2;
		else if (key == X_KEY_F)
			fractol->current = g_fractals + 3;
		else if (key == X_KEY_B)
			fractol->current = g_fractals + 4;
		else
			return (0);
		fractol->scale = 0.25;
		fractol->x = 0;
		fractol->y = 0;
	}
	return (render(fractol));
}

static int	mouse_move_hook(int x, int y, t_fractol *fractol)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		fractol->c = (float)x / WIDTH + (float)y / HEIGHT * I;
		return (render(fractol));
	}
	else
		return (0);
}

int			main(void)
{
	t_fractol	fractol;
	int			u;

	fractol.current = g_fractals;
	fractol.c = 0.285 + 0.013 * I;
	fractol.max_iter = 101;
	fractol.scale = 0.25;
	fractol.x = 0;
	fractol.y = 0;
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT + INFO_HEIGHT,
			"Fract'ol");
	fractol.ximg = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
	fractol.img = (int *)mlx_get_data_addr(fractol.ximg, &u, &u, &u);
	mlx_expose_hook(fractol.win, render, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_hook(fractol.win, X_KEYPRESS, X_KEYPRESSMASK, key_hook, &fractol);
	mlx_hook(fractol.win, X_MOTIONNOTIFY, X_POINTERMOTIONMASK, mouse_move_hook,
			&fractol);
	mlx_loop(fractol.mlx);
}
