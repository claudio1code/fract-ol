/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:03 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/30 16:38:59 by clados-s         ###   ########.fr       */
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
	fractol.addr = mlx_get_data_addr(fractol.img_ptr, &fractol.bpp,
			&fractol.line_length, &fractol.endian);
	fractol.max_inter = 150;
	if (ft_strncmp(fractol.name, "cinema", 7) == 0)
	{
		fractol.max_inter = 400;
		fractol.pos_x = -0.75;
		fractol.pos_y = 0.0;
		fractol.zoom = 1.0;
	}
	else
	{
		fractol.pos_x = 0;
		fractol.pos_y = 0;
		fractol.zoom = 1.0;
	}
	fractol.cplx_min_re = fractol.pos_x - (4.0 / fractol.zoom) / 2.0;
	fractol.cplx_max_re = fractol.pos_x + (4.0 / fractol.zoom) / 2.0;
	fractol.cplx_min_im = fractol.pos_y - (4.0 / fractol.zoom) / 2.0;
	fractol.cplx_max_im = fractol.pos_y + (4.0 / fractol.zoom) / 2.0;
	fractol.color_freq = 15.0;
	if (ft_strncmp(fractol.name, "cinema", 7) == 0)
		fractol.is_auto_zoom = 1;
	else
		fractol.is_auto_zoom = 0;
	fractol.mouse_x = WIDTH / 2;
	fractol.mouse_y = HEIGHT / 2;
	fractol.is_locked = 0;
	fractol.lock_x = 0;
	fractol.lock_y = 0;
	fractol.color_shift = 0;
	put_image(&fractol);

	mlx_hook(fractol.win_ptr, 17, 0, clean_exit, &fractol);
	mlx_hook(fractol.win_ptr, 2, 1L << 0, handle_key_relese, &fractol);
	mlx_mouse_hook(fractol.win_ptr, handle_mouse_click, &fractol);
	mlx_hook(fractol.win_ptr, 6, 1L << 6, handle_mouse_move, &fractol);
	mlx_loop_hook(fractol.mlx_ptr, loop_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);
	return (0);
}
