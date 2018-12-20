/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 09:13:46 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/20 12:15:31 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "ft/mlx.h"
#include "ft/str.h"
#include <stdlib.h>
#include <unistd.h>

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

static int	mousem_hook(int x, int y, t_fractol *fractol)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		fractol->c = (float)x / WIDTH + (float)y / HEIGHT * I;
		return (render(fractol));
	}
	else
		return (0);
}

#define USAGE "Usage: fractol [mandelbrot|julia|leaf|feigen|ship]\n"

int			main(int ac, char *av[])
{
	t_fractol	self;
	int			i;

	self.current = NULL;
	i = 0;
	if (ac == 2)
		while (i < 5)
			if (ft_strcmp(g_fractals[i++].name, av[1]) == 0)
			{
				self.current = g_fractals + i - 1;
				break ;
			}
	if (!self.current)
		return (write(2, USAGE, sizeof(USAGE) - 1) & 0 + 1);
	self = (t_fractol) { .current = self.current, .mlx = mlx_init(),
		.c = 0.285 + 0.013 * I, .max_iter = 101, .scale = 0.25, .x = 0, .y = 0
	};
	self.win = mlx_new_window(self.mlx, WIDTH, HEIGHT + INFO_HEIGHT, "Fractol");
	self.ximg = mlx_new_image(self.mlx, WIDTH, HEIGHT);
	self.img = (int *)mlx_get_data_addr(self.ximg, &i, &i, &i);
	mlx_expose_hook(self.win, render, &self);
	mlx_mouse_hook(self.win, mouse_hook, &self);
	mlx_hook(self.win, X_KEYPRESS, X_KEYPRESSMASK, key_hook, &self);
	mlx_hook(self.win, X_MOTIONNOTIFY, X_POINTERMOTIONMASK, mousem_hook, &self);
	mlx_loop(self.mlx);
}
