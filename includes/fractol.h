/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:18 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/22 14:29:02 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

# define KEY_ESC 65307
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_fractal
{
	void	*mlx_ptr;
	void	*win_ptr;

	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*name;
	double	r_julia;
	double	i_julia;
}t_fractal;

int		handle_key_realese(int keycode, t_fractal *fractal);
int		close_handle(t_fractal *fractal);
void	usage_input_and_exit(int flag);
int		julia_valid(char **argv, t_fractal *lst);
int		input_valid(int argc, char **argv, t_fractal *lst);

#endif