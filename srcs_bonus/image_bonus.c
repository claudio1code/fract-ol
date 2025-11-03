/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:26:14 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 11:48:14 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	get_color_from_angle(long double angle, t_fractol *data)
{
	double	normalizes;
	double	pi;
	int		color;
	double	freq;

	pi = 3.141592653589793;
	normalizes = (double)angle / (double)data->max_iter;
	freq = normalizes * 2 * pi * data->color_freq;
	data->r = (int)(127.5 * sin(freq + 0.0) + 127.5);
	data->g = (int)(127.5 * sin(freq + (2 * pi / 3.0)) + 127.5);
	data->b = (int)(127.5 * sin(freq + (4 * pi / 3.0)) + 127.5);
	color = (data->r) << 16 | (data->g) << 8 | (data->b);
	return (color);
}

static int	aux_pixel(t_fractol *data)
{
	int			color;
	long double	val;

	if (data->fractol == 2)
	{
		val = if_julia(data);
		if (val >= data->max_iter)
			color = 0x000000;
		else
			color = get_color_from_angle(val, data);
	}
	else if (data->fractol == 1)
	{
		val = mandelbrot(data);
		if (val >= data->max_iter)
			color = 0x000000;
		else
			color = get_color_from_angle(val, data);
	}
	else
	{
		val = newton_fractal(data);
		color = get_color_from_angle(val, data);
	}
	return (color);
}

static void	put_pixel_bonus(t_fractol *data, int x, int y)
{
	char		*addr;
	int			color;

	addr = data->addr + (y * data->line_length + x * (data->bpp / 8));
	color = aux_pixel(data);
	*(unsigned int *)addr = color;
}

void	put_image(t_fractol *fractol)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			map_pixel_to_complex(x, y, fractol);
			put_pixel_bonus(fractol, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
		fractol->img_ptr, 0, 0);
}
