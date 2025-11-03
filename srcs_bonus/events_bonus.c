/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:01:24 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:50:46 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	update_complex(t_fractol *fractol)
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

int	redraw_img(t_fractol *fractol)
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

int	handle_key_relese(int keycode, t_fractol *fractol)
{
	double		move_speed;

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
		fractol->pos_y += move_speed;
	else if (keycode == 65364)
		fractol->pos_y -= move_speed;
	else if (keycode == 65451)
		fractol->color_freq *= 1.1;
	else if (keycode == 65453)
		fractol->color_freq *= 0.90;
	else
		return (0);
	update_complex(fractol);
	redraw_img(fractol);
	return (0);
}
