/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:03 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/22 14:30:09 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	input_valid(argc, argv, &fractal);
	fractal.mlx_ptr = mlx_init();
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, WIDTH, HEIGHT, "fractal");
	fractal.img_ptr = mlx_new_image(fractal.mlx_ptr, WIDTH, HEIGHT);
	fractal.addr = mlx_get_data_addr(fractal.img_ptr, &fractal.bits_per_pixel,
			&fractal.line_length, &fractal.endian);
	mlx_put_image_to_window(fractal.mlx_ptr, fractal.win_ptr,
		fractal.img_ptr, 0, 0);
	mlx_key_hook(fractal.win_ptr, handle_key_realese, &fractal);
	mlx_hook(fractal.win_ptr, 17, 0, close_handle, &fractal);
	mlx_loop(fractal.mlx_ptr);
}
