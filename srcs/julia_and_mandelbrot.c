/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_and_mandelbrot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:47:32 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/27 12:10:26 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	if_julia(t_fractol *lst)
{
	long double	x;
	long double	y;
	int			i;
	long double	temp;

	x = lst->real;
	y = lst->imaginary;
	i = 0;
	while (i < lst->max_inter && ((x * x) + (y * y) <= 4))
	{
		temp = x * x - y * y + lst->r_julia;
		y = 2 * x * y + lst->i_julia;
		x = temp;
		i++;
	}
	return (i);
}

int	mandelbrot(t_fractol*fractol)
{
	double	a;
	double	b;
	double	a2;
	double	b2;
	int		i;

	a = 0.0;
	b = 0.0;
	a2 = 0.0;
	b2 = 0.0;
	i = 0;
	while (i < fractol->max_inter)
	{
		a2 = a * a;
		b2 = b * b;
		if (a2 + b2 > 4.0)
			return (i);
		b = 2 * a * b + fractol->imaginary;
		a = a2 - b2 + fractol->real;
		i++;
	}
	return (fractol->max_inter);
}
