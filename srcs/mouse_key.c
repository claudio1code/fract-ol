/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:01:24 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/22 15:11:39 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key_realese(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
		mlx_destroy_window(fractol->mlx_ptr, fractol->win_ptr);
		mlx_destroy_display(fractol->mlx_ptr);
		free(fractol->mlx_ptr);
		exit (0);
	}
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
