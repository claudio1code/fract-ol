/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:15:06 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/31 17:20:05 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	clean_exit(t_fractol *fractol)
{
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	if (fractol->win_ptr)
		mlx_destroy_window(fractol->mlx_ptr, fractol->win_ptr);
	if (fractol->mlx_ptr)
	{
		mlx_destroy_display(fractol->mlx_ptr);
		free(fractol->mlx_ptr);
	}
	if (fractol->name)
		free(fractol->name);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		clean_exit(fractol);
	return (0);
}

static void	update_complex(t_fractol *fractol)
{
	long double	range_re;
	long double	range_im;

	range_re = 4.0 / fractol->zoom;
	range_im = 4.0 / fractol->zoom;
	fractol->cplx_min_re = fractol->pos_x - range_re / 2.0;
	fractol->cplx_max_re = fractol->pos_x + range_re / 2.0;
	fractol->cplx_min_im = fractol->pos_y - range_im / 2.0;
	fractol->cplx_max_im = fractol->pos_y + range_im / 2.0;
}

int	handle_mouse(int button, t_fractol *fractol)
{
	if (button == 4)
		fractol->zoom *= 1.10;
	else if (button == 5)
		fractol->zoom *= 0.90;
	else
		return (0);
	update_complex_range(fractol);
	put_image(fractol);
	return (0);
}
