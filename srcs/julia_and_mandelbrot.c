/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_and_mandelbrot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:47:32 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/27 06:14:15 by claudio          ###   ########.fr       */
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

void	put_pixel(t_fractol *data, int x, int y)
{
	char	*addr;
	int		color;
	int		i;
	int		j;

	i = 0;
	addr = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	if (data->fractol == 2)
		i = if_julia(data);
	else if (data->fractol == 1)
		i = mandelbrot(data);
	if (i == data->max_inter)
		color = 0x000000;
	else
	{
		j = (int)(256.0 * sqrt((double)i / data->max_inter));
		if (j > 255)
			j = 255;
		color = (j << 16) | (j << 8) | j;
	}
	*(unsigned int *)addr = color;
}

void	my_mlx_pixel_put(t_fractol *img, int x, int y, int color)
{
	char	*dst;
	int		red;

	if (color < 11)
		color = 0;
	else
	{
		red = color * 3.0;
		color = (70 << 16) | (red << 8) | 70;
	}
	if ((x < 0 || y < 0) || (x > WIDTH || y > HEIGHT))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	map_pixel_to_complex(int px, int py, t_fractol *fractal)
{
	long double real_range;
    long double img_range;
    long double center_re;
    long double center_im;

	center_re = fractal->pos_x;
    center_im = fractal->pos_y;
real_range = (fractal->complex_max_re - fractal->complex_min_re)
			/ fractal->zoom;
    img_range = (fractal->complex_max_im - fractal->complex_min_im)
			/ fractal->zoom;
	fractal->real = fractal->complex_min_re + ((long double)px / (WIDTH - 1))
		* real_range;
	fractal->imaginary = fractal->complex_max_im - ((long double)py
			/ (HEIGHT - 1)) * img_range;
	fractal->complex_min_re = center_re - real_range / 2.0;
	fractal->complex_max_re = center_re + real_range / 2.0;
	fractal->complex_min_im = center_im - img_range / 2.0;
	fractal->complex_max_im = center_im + img_range / 2.0;
	fractal->real = fractal->complex_min_re + ((long double)px / (WIDTH - 1))
		* (fractal->complex_max_re - fractal->complex_min_re);
	fractal->imaginary = fractal->complex_max_im - ((long double)py
		/ (HEIGHT - 1)) * (fractal->complex_max_im - fractal->complex_min_im);
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
