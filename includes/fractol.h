/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:18 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/23 17:00:06 by clados-s         ###   ########.fr       */
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
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	char		*name;
	long double	r_julia;
	long double	i_julia;
	long double	real;
	long double	imaginary;
	int			fractol;


	int			max_inter;
	long double	pos_x;
	long double	pos_y;
}t_fractol;

int		handle_key_realese(int keycode, t_fractol *fractol);
int		close_handle(t_fractol *fractol);
void	usage_input_and_exit(int flag);
int		julia_valid(char **argv, t_fractol *lst);
int		input_valid(int argc, char **argv, t_fractol *lst);
void	put_pixel(t_fractol *data, int x, int y);
void	put_image(t_fractol *fractol);

#endif