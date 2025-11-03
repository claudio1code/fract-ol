/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:29:49 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:14:25 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	init_fractol(t_fractol *f)
{
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		exit(EXIT_FAILURE);
	f->win_ptr = mlx_new_window(f->mlx_ptr, WIDTH, HEIGHT, "fractol");
	if (!f->win_ptr)
	{
		free(f->mlx_ptr);
		exit(EXIT_FAILURE);
	}	
	f->img_ptr = mlx_new_image(f->mlx_ptr, WIDTH, HEIGHT);
	if (!f->img_ptr)
	{
		mlx_destroy_window(f->mlx_ptr, f->win_ptr);
		mlx_destroy_display(f->mlx_ptr);
		free(f->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	f->addr = mlx_get_data_addr(f->img_ptr, &f->bpp, &f->line_length,
			&f->endian);
}

static void	register_hooks(t_fractol *fractol)
{
	mlx_key_hook(fractol->win_ptr, handle_key_relese, fractol);
	mlx_hook(fractol->win_ptr, DestroyNotify, NoEventMask, clean_exit, fractol);
	mlx_mouse_hook(fractol->win_ptr, handle_mouse_click, fractol);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	fractol.fractol = input_valid(argc, argv, &fractol);
	init_fractol(&fractol);
	fractol.max_iter = 142;
	fractol.pos_x = 0;
	fractol.pos_y = 0;
	fractol.zoom = 1.0;
	fractol.cplx_max_im = 2.0;
	fractol.cplx_min_im = -2.0;
	fractol.cplx_max_re = 2.0;
	fractol.cplx_min_re = -2.0;
	fractol.color_freq = 15.0;
	put_image(&fractol);
	register_hooks(&fractol);
	mlx_loop(fractol.mlx_ptr);
	return (0);
}
