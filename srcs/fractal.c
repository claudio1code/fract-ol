/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:03 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/21 10:03:33 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	main(void)
{
	t_fractal	fractal;

	fractal.mlx_ptr = mlx_init();
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, 1920, 1080, "fractal");
	fractal.img.img_ptr = mlx_new_image(fractal.mlx_ptr, 1920, 1080);
	fractal.img.addr = mlx_get_data_addr(fractal.img.img_ptr, &fractal.img.bits_per_pixel,
			&fractal.img.line_length, &fractal.img.endian);
	// draw_squad(&fractal.img, 300, 400, 600, 600);
	mlx_put_image_to_window(fractal.mlx_ptr, fractal.win_ptr, fractal.img.img_ptr, 0, 0);
	mlx_key_hook(fractal.win_ptr, handle_key_realese, &fractal);
	mlx_hook(fractal.win_ptr, 17, 0, close_window, &fractal);
	mlx_loop(fractal.mlx_ptr);