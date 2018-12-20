/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 10:28:32 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/20 10:40:08 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

t_fractal	g_fractals[] = {
	{"mandelbrot", mandelbrot },
	{"julia", julia },
	{"leaf", leaf },
	{"feigen", feigen },
	{"ship", burning_ship },
};

size_t	mandelbrot(t_complex c, size_t max_iter)
{
	t_complex	z;
	size_t		i;

	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

size_t	burning_ship(t_complex c, size_t max_iter)
{
	t_complex	z;
	size_t		i;

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

size_t	leaf(t_complex c, size_t max_iter)
{
	size_t		i;
	t_complex	z;

	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = ccos(z / c);
		i++;
	}
	return (i);
}

size_t	feigen(t_complex c, size_t max_iter)
{
	size_t		i;
	t_complex	z;
	t_complex	c3;

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
