/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:08:22 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/30 16:07:18 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color_from_palette(long double i, t_fractol *data)
{
	double	normalizes;
	double	pi;
	int		color;
	double	freq;
	int		r;
	int		g;
	int		b;

	pi = 3.141592653589793;
	normalizes = (double)i / (double)data->max_inter;
	freq = normalizes * 2 * pi * data->color_freq + data->color_shift * 0.1;
	r = (int)(127.5 * sin(freq + 0.0) + 127.5);
	g = (int)(127.5 * sin(freq + (2 * pi / 3.0)) + 127.5);
	b = (int)(127.5 * sin(freq + (4 * pi / 3.0)) + 127.5);
	color = (r) << 16 | (g) << 8 | (b);
	return (color);
}

void	map_pixel_to_complex(int px, int py, t_fractol *fractal, \
		long double *re, long double *im)
{
	*re = fractal->cplx_min_re + ((long double)px / (WIDTH - 1))
		* (fractal->cplx_max_re - fractal->cplx_min_re);
	*im = fractal->cplx_max_im - ((long double)py
			/ (HEIGHT - 1)) * (fractal->cplx_max_im - fractal->cplx_min_im);
}

static void	process_pixel(t_fractol *data, int x, int y)
{
	char		*addr;
	int			color;
	long double	i;
	long double	re;
	long double	im;

	i = 0;
	map_pixel_to_complex(x, y, data, &re, &im);
	if (data->fractol == 2)
		i = if_julia(data, re, im);
	else if (data->fractol == 1)
		i = mandelbrot(data, re, im);
	if (i >= data->max_inter)
		color = 0x000000;
	else
		color = get_color_from_palette(i, data);
	addr = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)addr = color;
}

void	*render_thread(void *arg)
{
	t_thread_data	*t_data;
	int				x;
	int				y;

	t_data = (t_thread_data *)arg;
	y = t_data->id;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			process_pixel(t_data->fractol, x, y);
			x++;
		}
		y += NUM_THREADS;
	}
	return (NULL);
}

void	put_image(t_fractol *fractol)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	t_data[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		t_data[i].fractol = fractol;
		t_data[i].id = i;
		pthread_create(&threads[i], NULL, render_thread, &t_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
		fractol->img_ptr, 0, 0);
}