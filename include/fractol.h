/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:42:30 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/20 11:45:38 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>
# include <complex.h>

# define WIDTH 750
# define HEIGHT 500
# define INFO_HEIGHT 50

typedef _Complex double	t_complex;
typedef size_t			(*t_fractal_fn)();

typedef	struct			s_fractal {
	char			*name;
	t_fractal_fn	fn;
}						t_fractal;

typedef struct			s_fractol {
	void		*mlx;
	void		*win;
	void		*ximg;
	int			*img;
	float		scale;
	size_t		max_iter;
	int			x;
	int			y;
	t_complex	c;
	t_fractal	*current;
}						t_fractol;

typedef struct			s_worker_arg
{
	t_fractol	*fractol;
	int			start_y;
	int			end_y;
}						t_worker_arg;

int						render(t_fractol *fractol);

size_t					mandelbrot(t_complex c, size_t max_iter);
size_t					leaf(t_complex c, size_t max_iter);
size_t					feigen(t_complex c, size_t max_iter);
size_t					burning_ship(t_complex c, size_t max_iter);
size_t					julia(t_complex z, size_t max_iter, t_complex c);

extern t_fractal		g_fractals[];

#endif
