/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:08:22 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 09:55:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color_from_palette(long double i, t_fractol *data)
{
	double	normalizes;
	double	pi;
	int		color;
	double	freq;

	pi = 3.141592653589793;
	normalizes = (double)i / (double)data->max_iter;
	freq = normalizes * 2 * pi * data->color_freq;
	data->r = (int)(127.5 * sin(freq + 0.0) + 127.5);
	data->g = (int)(127.5 * sin(freq + (2 * pi / 3.0)) + 127.5);
	data->b = (int)(127.5 * sin(freq + (4 * pi / 3.0)) + 127.5);
	color = (data->r) << 16 | (data->g) << 8 | (data->b);
	return (color);
}

static void	put_pixel(t_fractol *data, int x, int y)
{
	char		*addr;
	int			color;
	long double	i;

	i = 0;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	addr = data->addr + (y * data->line_length
			+ x * (data->bpp / 8));
	if (data->fractol == 2)
		i = if_julia(data);
	else if (data->fractol == 1)
		i = mandelbrot(data);
	if (i >= data->max_iter)
		color = 0x000000;
	else
		color = get_color_from_palette(i, data);
	*(unsigned int *)addr = color;
}

void	map_pixel_to_complex(int px, int py, t_fractol *fractal)
{
	fractal->real = fractal->cplx_min_re + ((long double)px / (WIDTH - 1))
		* (fractal->cplx_max_re - fractal->cplx_min_re);
	fractal->imaginary = fractal->cplx_max_im - ((long double)py
			/ (HEIGHT - 1)) * (fractal->cplx_max_im - fractal->cplx_min_im);
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
			put_pixel(fractol, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
		fractol->img_ptr, 0, 0);
}
