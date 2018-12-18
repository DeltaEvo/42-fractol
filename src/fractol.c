/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 09:13:46 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/18 16:31:43 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "ft/io.h"
#include "ft/mem.h"
#include "ft/mlx.h"
#include "ft/convert.h"
#include <stdint.h>
#include <stddef.h>
#include <complex.h>
#include <math.h>

size_t	mandelbrot(t_complex c, size_t max_iter, t_complex unu)
{
	t_complex	z;
	size_t		i;

	(void)unu;
	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

size_t	burning_ship(t_complex c, size_t max_iter, t_complex unu)
{
	t_complex	z;
	size_t		i;

	(void)unu;
	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c;
		z = fabs(creal(z)) + I * fabs(cimag(z));
		i++;
	}
	return (i);
}

size_t	julia(t_complex z, size_t max_iter, t_complex c)
{
	size_t	i;

	i = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

size_t	leaf(t_complex c, size_t max_iter, t_complex cu)
{
	size_t		i;
	t_complex	z;

	i = 0;
	z = 0;
	(void)cu;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = ccos(z / c);
		i++;
	}
	return (i);
}

size_t	feigen(t_complex c, size_t max_iter, t_complex un)
{
	size_t		i;
	t_complex	z;
	t_complex	c3;

	(void)un;
	i = 0;
	z = 0;
	c3 = c * c * c;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c3 - 1.401155;
		i++;
	}
	return (i);
}

#define WIDTH 750
#define HEIGHT 500
#define INFO_HEIGHT 50
#define HELP1 "m: Madelbrot  j: Julia  b: Burning Ship"
#define HELP2 "l: Leaf       f: Feigen"
#define MCOL 0xFFFFFF

int	render(t_fractol *fractol)
{
	int			x;
	int			y;
	int			res;
	t_int_str	str;

	x = 0;
	mlx_clear_window(fractol->mlx, fractol->win);
	ft_memset(fractol->img, 0, WIDTH * HEIGHT * 4);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			res = fractol->current->fn(
				1.5 * ((x - WIDTH / 2.0) / (fractol->scale * WIDTH)
					+ fractol->x / (float)WIDTH) + ((y - HEIGHT / 2.0) /
					(fractol->scale * HEIGHT) + fractol->y / (float)HEIGHT) * I,
				fractol->max_iter,
				fractol->c);
			fractol->img[y * WIDTH + x] = res * 0xFFFFFF / fractol->max_iter;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->ximg, 0, 0);
	mlx_pixel_put(fractol->mlx, fractol->win, WIDTH / 2, HEIGHT / 2, 0xFF0000);
	mlx_string_put(fractol->mlx, fractol->win, 5, HEIGHT, MCOL, "Iterations:");
	str = ft_uint_to_str(fractol->max_iter);
	mlx_string_put(fractol->mlx, fractol->win, 120, HEIGHT, MCOL, str.str);
	mlx_string_put(fractol->mlx, fractol->win, 5, HEIGHT + 20, MCOL, "X:");
	str = ft_int_to_str(fractol->x);
	mlx_string_put(fractol->mlx, fractol->win, 30, HEIGHT + 20, MCOL, str.str);
	mlx_string_put(fractol->mlx, fractol->win, 120, HEIGHT + 20, MCOL, "Y:");
	str = ft_int_to_str(fractol->y);
	mlx_string_put(fractol->mlx, fractol->win, 145, HEIGHT + 20, MCOL, str.str);
	mlx_string_put(fractol->mlx, fractol->win, 250, HEIGHT, MCOL, HELP1);
	mlx_string_put(fractol->mlx, fractol->win, 250, HEIGHT + 20, MCOL, HELP2);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
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

int	key_hook(int key, t_fractol *fractol)
{
	if (key == X_KEY_UP)
		fractol->y -= 100 / fractol->scale;
	else if (key == X_KEY_DOWN)
		fractol->y += 100 / fractol->scale;
	else if (key == X_KEY_LEFT)
		fractol->x -= 100 / fractol->scale;
	else if (key == X_KEY_RIGHT)
		fractol->x += 100 / fractol->scale;
	else if (key == X_KEY_M)
		fractol->current = g_fractals;
	else if (key == X_KEY_J)
		fractol->current = g_fractals + 1;
	else if (key == X_KEY_L)
		fractol->current = g_fractals + 2;
	else if (key == X_KEY_F)
		fractol->current = g_fractals + 3;
	else if (key == X_KEY_B)
		fractol->current = g_fractals + 4;
	else if (key == X_KEY_PLUS)
		fractol->max_iter += 25;
	else if (key == X_KEY_MINUS && fractol->max_iter >= 25)
		fractol->max_iter -= 25;
	return (render(fractol));
}

int	mouse_move_hook(int x, int y, t_fractol *fractol)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		fractol->c = (float)x / WIDTH + (float)y / HEIGHT * I;
		return (render(fractol));
	}
	else
		return (0);
}

int	main(void)
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
