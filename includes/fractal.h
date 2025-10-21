/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:18 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/21 15:20:02 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H

# define FRACTAL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

# define KEY_ESC 65307
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_fractal
{
	void		*mlx_ptr;
	void		*win_ptr;

	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}t_fractal;

int		handle_key_realese(int keycode, t_fractal *fractal);
int		close_handle(t_fractal *fractal);

#endif