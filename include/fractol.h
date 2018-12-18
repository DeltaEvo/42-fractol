/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:42:30 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/18 16:13:34 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>
# include <complex.h>

typedef _Complex double	t_complex;
typedef size_t			(*t_fractal_fn)(t_complex z, size_t max, t_complex c);

typedef	struct			s_fractal {
	char			*name;
	t_fractal_fn	fn;
	t_complex		start;
	t_complex		end;
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

size_t					mandelbrot(t_complex c, size_t max_iter, t_complex cu);
size_t					leaf(t_complex c, size_t max_iter, t_complex cu);
size_t					feigen(t_complex c, size_t max_iter, t_complex cu);
size_t					burning_ship(t_complex c, size_t max_iter,
		t_complex cu);
size_t					julia(t_complex z, size_t max_iter, t_complex c);

t_fractal	g_fractals[] = {
	{"Mandelbrot", mandelbrot, -2 + -I, 1 + I },
	{"Julia", julia, -2 + -I, 1 + I },
	{"Leaf", leaf, -2 + -I, 1 + I },
	{"Feigen", feigen, -2 + -I, 1 + I },
	{"Ship", burning_ship, -2 + -I, 1 + I },
};

#endif
