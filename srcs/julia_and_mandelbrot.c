/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_and_mandelbrot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:47:32 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/23 15:16:37 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	if_julia(t_fractol *lst)
{
	long double	x;
	long double	y;
	int			i;
	long double	temp;

	x = lst->real;
	y = lst->imaginary;
	i = 0;
	while (i < lst->max_inter && ((x * x) + (y * y) <= 4))
	{
		temp = x * x - y * y + lst->r_julia;
		y = 2 * x * y + lst->i_julia;
		x = temp;
		i++;
	}
	return (i);
}

int	put_pixel(t_fractol *data, int x, int y)
{
	char	*addr;
	int		color;
	int		i;
	int		j;

	addr = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	i = if_julia(data);
	if (i == data->max_inter)
		color = 0x000000;
	else
	{
		j = (int)(256.0 * sqrt((double)i / data->max_inter));
		if (j > 255)
			j = 255;
		color = (j << 16) | (j << 8) | j;
	}
	*(unsigned int *)addr = color;
}

void	put_image(t_fractol fractol)
{
	
}