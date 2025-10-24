/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:01:24 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/24 13:35:50 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_fractol *fractol)
{
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	if (fractol->win_ptr)
		mlx_destroy_win_ptr(fractol->mlx_ptr, fractol->win_ptr);
	if (fractol->mlx_ptr)
	{
		mlx_destroy_display(fractol->mlx_ptr);
		free(fractol->mlx_ptr);
	}
	exit(0);
	return (0);
}

int	handle_key_realese(int keycode, t_fractol *fractol)
{
	double		move_speed;

	move_speed = 0.1 / fractol->zoom;
	if (keycode == KEY_ESC)
		close_window(fractol);
	else if (keycode == 65361)
		fractol->pos_x -= move_speed;
	else if (keycode == 65363)
		fractol->pos_x += move_speed;
	else if (keycode == 65362)
		fractol->pos_y += move_speed;
	else if (keycode == 65364)
		fractol->pos_y -= move_speed;
	else
		return (0);
	mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	fractol->img_ptr = mlx_get_data_addr(fractol->img_ptr,
			&fractol->bits_per_pixel, &fractol->line_length, &fractol->endian);
	put_image(fractol);
	return (0);
}

int	close_handle(t_fractol *fractol)
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
	exit (0);
	return (0);
}
