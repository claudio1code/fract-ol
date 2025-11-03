/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:53:07 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 10:16:58 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

long double	if_julia(t_fractol *lst)
{
	long double	x;
	long double	y;
	long double	i;
	long double	temp;

	x = lst->real;
	y = lst->imaginary;
	i = 0;
	while (i < lst->max_iter && ((x * x) + (y * y) <= 4.0L))
	{
		temp = x * x - y * y + lst->r_julia;
		y = 2.0L * x * y + lst->i_julia;
		x = temp;
		i++;
	}
	return (i);
}

long double	mandelbrot(t_fractol*fractol)
{
	long double	a;
	long double	b;
	long double	a2;
	long double	b2;
	long double	i;

	a = 0.0;
	b = 0.0;
	a2 = 0.0;
	b2 = 0.0;
	i = 0;
	while (i < fractol->max_iter)
	{
		a2 = a * a;
		b2 = b * b;
		if (a2 + b2 > 4.0L)
		{
			i += (i + 1.0 - log(log(sqrt(a2 + b2))) / log(2.0));
			return (i);
		}
		b = 2 * a * b + fractol->imaginary;
		a = a2 - b2 + fractol->real;
		i++;
	}
	return ((long double)fractol->max_iter);
}

long double	newton_fractal(t_fractol *fractol)
{
	long double	z[2];
	long double	p[2];
	long double	dp[2];
	long double	temp[2];
	int			iter;

	z[0] = fractol->real;
	z[1] = fractol->imaginary;
	iter = -1;
	while (++iter < 40)
	{
		p[0] = (z[0] * z[0] * z[0]) - (3.0L * z[0] * z[1] * z[1]) - 1.0L;
		p[1] = (3.0L * z[0] * z[0] * z[1]) - (z[1] * z[1] * z[1]);
		dp[0] = 3.0L * (z[0] * z[0] - z[1] * z[1]);
		dp[1] = 6.0L * z[0] * z[1];
		temp[0] = dp[0] * dp[0] + dp[1] * dp[1];
		if (temp[0] < 1e-9)
			break ;
		temp[1] = (p[0] * dp[0] + p[1] * dp[1]) / temp[0];
		dp[1] = (p[1] * dp[0] - p[0] * dp[1]) / temp[0];
		z[0] = z[0] - temp[1];
		z[1] = z[1] - dp[1];
	}
	return (atan2(z[1], z[0]));
}
