/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:18 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/30 16:32:37 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define KEY_ESC 65307
# define WIDTH 800
# define HEIGHT 600
# define _USE_MATH_DEFINES

typedef struct s_fractol
{
	void		*mlx_ptr;
	void		*win_ptr;

	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;

	char		*name;
	long double	r_julia;
	long double	i_julia;
	long double	real;
	long double	imaginary;
	int			fractol;


	int			max_inter;
	long double	zoom;
	long double	pos_x;
	long double	pos_y;

	long double	cplx_min_re;
	long double	cplx_max_re;
	long double	cplx_min_im;
	long double	cplx_max_im;

	long double	color_freq;
	int			r;
	int			g;
	int			b;
}t_fractol;

int			handle_key_relese(int keycode, t_fractol *fractol);
int			julia_valid(char **argv, t_fractol *lst);
int			input_valid(int argc, char **argv, t_fractol *lst);
void		put_image(t_fractol *fractol);
long double	mandelbrot(t_fractol*fractol);
int			handle_mouse_click(int button, int x, int y, t_fractol *fractol);
void		map_pixel_to_complex(int px, int py, t_fractol *fractal);
long double	if_julia(t_fractol *lst);
int			clean_exit(t_fractol *fractol);

#endif