/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 10:42:48 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/20 11:47:21 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <pthread.h>
#include "fractol.h"
#include "ft/mem.h"
#include "ft/convert.h"

#define HELP1 "m: Madelbrot  j: Julia  b: Burning Ship"
#define HELP2 "l: Leaf       f: Feigen"
#define MCOL 0xFFFFFF

static int	infos(t_fractol *fractol)
{
	t_int_str	str;

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

void		*render_worker(t_worker_arg *arg)
{
	const t_fractol	*fractol = arg->fractol;
	int				x;
	int				y;
	int				res;

	y = arg->start_y;
	while (y < arg->end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			res = fractol->current->fn(
				1.5 * ((x - WIDTH / 2.0) / (fractol->scale * WIDTH)
					+ fractol->x / (float)WIDTH) + ((y - HEIGHT / 2.0) /
					(fractol->scale * HEIGHT) + fractol->y / (float)HEIGHT) * I,
				fractol->max_iter,
				fractol->c);
			fractol->img[y * WIDTH + x] = res * 0xFFFFFF / fractol->max_iter;
			x++;
		}
		y++;
	}
	return (NULL);
}

#define NUM_THREADS 4

int			render(t_fractol *fractol)
{
	pthread_t		threads[NUM_THREADS];
	t_worker_arg	args[NUM_THREADS];
	int				i;

	mlx_clear_window(fractol->mlx, fractol->win);
	ft_memset(fractol->img, 0, WIDTH * HEIGHT * 4);
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i] = (t_worker_arg) {
			.fractol = fractol,
			.start_y = i * (HEIGHT / NUM_THREADS),
			.end_y = (i + 1) * HEIGHT / NUM_THREADS
		};
		pthread_create(threads + i, NULL, (void *)render_worker, args + i);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->ximg, 0, 0);
	return (infos(fractol));
}
