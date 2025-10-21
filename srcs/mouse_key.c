/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:01:24 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/21 11:00:32 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	handle_key_realese(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(fractal->mlx_ptr, fractal->img_ptr);
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		exit (0);
	}
	return (0);
}

int	close_window(t_fractal *fractal)
{
	if (fractal->img_ptr)
		mlx_destroy_image(fractal->mlx_ptr, fractal->img_ptr);
	if (fractal->win_ptr)
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	if (fractal->mlx_ptr)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
	}
	exit (0);
	return (0);
}
