/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:03 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/24 11:41:27 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	fractol.fractol = input_valid(argc, argv, &fractol);
	fractol.mlx_ptr = mlx_init();
	fractol.win_ptr = mlx_new_window(fractol.mlx_ptr, WIDTH, HEIGHT, "fractol");
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, WIDTH, HEIGHT);
	fractol.addr = mlx_get_data_addr(fractol.img_ptr, &fractol.bits_per_pixel,
			&fractol.line_length, &fractol.endian);
	fractol.max_inter = 200;
	fractol.pos_x = 0;
	fractol.pos_y = 0;
	fractol.complex_max_im = 2.0;
	fractol.complex_min_im = -2.0;
	fractol.complex_max_re = 2.0;
	fractol.complex_min_re = -2.0;
	put_image(&fractol);
	mlx_key_hook(fractol.win_ptr, handle_key_realese, &fractol);
	mlx_hook(fractol.win_ptr, 17, 0, close_handle, &fractol);
	mlx_loop(fractol.mlx_ptr);
	return (0);
}
