/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:18 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/27 14:38:09 by clados-s         ###   ########.fr       */
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
# define WIDTH 1920
# define HEIGHT 1080

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
}t_fractol;

int		handle_key_realese(int keycode, t_fractol *fractol);
int		close_handle(t_fractol *fractol);
void	usage_input_and_exit(int flag);
int		julia_valid(char **argv, t_fractol *lst);
int		input_valid(int argc, char **argv, t_fractol *lst);
void	put_pixel(t_fractol *data, int x, int y);
void	put_image(t_fractol *fractol);
void	map_pixel_to_complex(int px, int py, t_fractol *fractal);
int		close_window(t_fractol *fractol);
int		mandelbrot(t_fractol*fractol);
int		handle_mouse_click(int button, t_fractol *fractol);
int		if_julia(t_fractol *lst);
int		new_img(t_fractol *fractol);

#endif