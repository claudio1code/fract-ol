/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:01:24 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/30 17:08:23 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	redraw_image(t_fractol *fractol)
{
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	if (!fractol->img_ptr)
		clean_exit(fractol);
	fractol->addr = mlx_get_data_addr(fractol->img_ptr,
			&fractol->bpp, &fractol->line_length, &fractol->endian);
	put_image(fractol);
}

int	handle_key_relese(int keycode, t_fractol *fractol)
{
	double		move_speed;
	long double	range_re;
	long double	range_im;

	if (fractol->zoom <= 0.0)
		fractol->zoom = 1.0;
	move_speed = 0.1 / fractol->zoom;
	if (keycode == KEY_ESC)
		clean_exit(fractol);
	else if (keycode == 65361)
		fractol->pos_x -= move_speed;
	else if (keycode == 65363)
		fractol->pos_x += move_speed;
	else if (keycode == 65362)
		fractol->pos_y -= move_speed;
	else if (keycode == 65364)
		fractol->pos_y += move_speed;
	else if (keycode == 65451)
		fractol->color_freq *= 1.1;
	else if (keycode == 65453)
		fractol->color_freq *= 0.90;
	else if (keycode == 32)
		fractol->is_auto_zoom = !fractol->is_auto_zoom;
	else
		return (0);
	range_re = 4.0 / fractol->zoom;
	range_im = 4.0 / fractol->zoom;
	fractol->cplx_min_re = fractol->pos_x - range_re / 2.0;
	fractol->cplx_max_re = fractol->pos_x + range_re / 2.0;
	fractol->cplx_min_im = fractol->pos_y - range_im / 2.0;
	fractol->cplx_max_im = fractol->pos_y + range_im / 2.0;
	redraw_image(fractol);
	return (0);
}

long double	apply_zoom(int button, t_fractol *fractol)
{
	long double	zoom_factor;

	zoom_factor = 1.0;
	if (button == 4)
	{
		zoom_factor = 1.10;
		fractol->zoom *= zoom_factor;
	}
	else if (button == 5)
	{
		zoom_factor = 0.9;
		fractol->zoom *= zoom_factor;
	}
	return (zoom_factor);
}

void	update_view(t_fractol *f, long double m_re, long double m_im,
													long double factor)
{
	long double	offset_re;
	long double	offset_im;
	long double	range_re;
	long double	range_im;

	offset_re = m_re - f->pos_x;
	offset_im = m_im - f->pos_y;
	f->pos_x = m_re - (offset_re / factor);
	f->pos_y = m_im - (offset_im / factor);
	range_re = 4.0 / f->zoom;
	range_im = 4.0 / f->zoom;
	f->cplx_min_re = f->pos_x - range_re / 2.0;
	f->cplx_max_re = f->pos_x + range_re / 2.0;
	f->cplx_min_im = f->pos_y - range_im / 2.0;
	f->cplx_max_im = f->pos_y + range_im / 2.0;
}

int	new_img(t_fractol *fractol)
{
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	if (!fractol->img_ptr)
		clean_exit(fractol);
	fractol->addr = mlx_get_data_addr(fractol->img_ptr, &fractol->bpp,
			&fractol->line_length, &fractol->endian);
	put_image(fractol);
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_fractol *fractol)
{
	long double	mouse_re;
	long double	mouse_im;
	long double	zoom_factor;

	if (button != 4 && button != 5)
		return (0);
	map_pixel_to_complex(x, y, fractol, &mouse_re, &mouse_im);
	zoom_factor = apply_zoom(button, fractol);
	update_view(fractol, mouse_re, mouse_im, zoom_factor);
	new_img(fractol);
	return (0);
}

int	handle_mouse_move(int x, int y, t_fractol *fractol)
{
	fractol->mouse_x = x;
	fractol->mouse_y = y;
	return (0);
}

int	loop_hook(t_fractol *fractol)
{
	long double	mouse_re;
	long double	mouse_im;
	long double	zoom_factor;

	if (!fractol->is_auto_zoom)
		return (0);
	if (ft_strncmp(fractol->name, "cinema", 7) == 0)
	{
		mouse_re = -1.786124;
		mouse_im = 0.0;
	}
	else
		map_pixel_to_complex(fractol->mouse_x, fractol->mouse_y, fractol,
			&mouse_re, &mouse_im);
	fractol->color_shift++;
	zoom_factor = 1.01;
	fractol->zoom *= zoom_factor;
	if (ft_strncmp(fractol->name, "cinema", 7) != 0)
	{
		if (fractol->zoom > 150.0)
			fractol->max_inter = (int)(150 + log(fractol->zoom / 150.0) * 700);
		else
			fractol->max_inter = 150;
	}
	update_view(fractol, mouse_re, mouse_im, zoom_factor);
	new_img(fractol);
	return (0);
}