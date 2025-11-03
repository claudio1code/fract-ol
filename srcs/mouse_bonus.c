/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:53:26 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 11:00:56 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static long double	apply_zoom(int button, t_fractol *fractol)
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

static void	update_view(t_fractol *f, long double m_re, long double m_im,
													long double factor)
{
	long double	offset_re;
	long double	offset_im;

	offset_re = m_re - f->pos_x;
	offset_im = m_im - f->pos_y;
	f->pos_x = m_re - (offset_re / factor);
	f->pos_y = m_im - (offset_im / factor);
	update_complex_range(f);
}

int	handle_mouse_click(int button, int x, int y, t_fractol *fractol)
{
	long double	mouse_re;
	long double	mouse_im;
	long double	zoom_factor;

	if (button != 4 && button != 5)
		return (0);
	map_pixel_to_complex(x, y, fractol);
	mouse_re = fractol->real;
	mouse_im = fractol->imaginary;
	zoom_factor = apply_zoom(button, fractol);
	update_view(fractol, mouse_re, mouse_im, zoom_factor);
	redraw_img(fractol);
	return (0);
}
