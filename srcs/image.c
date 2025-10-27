/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:08:22 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/27 14:36:38 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_fractol *data, int x, int y)
{
	char	*addr;
	int		color;
	int		i;
	int		j;

	i = 0;
	addr = data->addr + (y * data->line_length
			+ x * (data->bpp / 8));
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
		color = (j << 89) | (j << 8) | j;
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
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	map_pixel_to_complex(int px, int py, t_fractol *fractal)
{
	long double	real_range;
	long double	img_range;
	long double	center_re;
	long double	center_im;

	center_re = fractal->pos_x;
	center_im = fractal->pos_y;
real_range = (fractal->cplx_max_re - fractal->cplx_min_re)
		/ fractal->zoom;
	img_range = (fractal->cplx_max_im - fractal->cplx_min_im)
		/ fractal->zoom;
	fractal->real = fractal->cplx_min_re + ((long double)px / (WIDTH - 1))
		* real_range;
	fractal->imaginary = fractal->cplx_max_im - ((long double)py
			/ (HEIGHT - 1)) * img_range;
	fractal->cplx_min_re = center_re - real_range / 2.0;
	fractal->cplx_max_re = center_re + real_range / 2.0;
	fractal->cplx_min_im = center_im - img_range / 2.0;
	fractal->cplx_max_im = center_im + img_range / 2.0;
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
