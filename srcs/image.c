/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:08:22 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/27 16:05:07 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel(t_fractol *data, int x, int y)
{
	char	*addr;
	int		color;
	int		depth_color;
	int		i;

	i = 0;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	addr = data->addr + (y * data->line_length
			+ x * (data->bpp / 8));
	if (data->fractol == 2)
		i = if_depth_colorulia(data);
	else if (data->fractol == 1)
		i = mandelbrot(data);
	if (i == data->max_inter)
		color = 0x000000;
	else
	{
		depth_color = (i * 255) / data->max_inter;
		if (depth_color > 255)
			depth_color = 255;
		color = (depth_color / 2 << 16) | (depth_color << 8) | depth_color;
		// color = (i * 15) << 16 | (i * 7) << 8 | (i * 22);
	}
	*(unsigned int *)addr = color;
}

void	map_pixel_to_complex(int px, int py, t_fractol *fractal)
{
	long double	real_range;
	long double	img_range;
	long double	center_re;
	long double	center_im;

	real_range = 4.0L / fractal->zoom;
	img_range = 4.0L / fractal->zoom;
	center_im = 0.0L;
	center_re = 0.0L;
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
