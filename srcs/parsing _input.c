/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing _input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:03:43 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/22 14:28:41 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage_input_and_exit(int flag)
{
	if (flag == 1)
	{
		write(1, "Uso incorreto.\n", 15);
		write(1, "Opções disponíveis:\n", 20);
		write(1, "  ./fractal Mandelbrot\n", 24);
		write(1, "  ./fractal Julia <c_real> <c_imag>\n", 37);
		exit(EXIT_FAILURE);
	}
	else if (flag == 2)
	{
		write (1, "Julia value is invalid. Exemples valids:\n", 41);
		write(1, "Exemplo para Julia: ./fractal Julia -0.8 0.156\n", 49);
		exit(EXIT_FAILURE);
	}
}

int	julia_valid(char **argv, t_fractal *lst)
{
	int	r_arg;
	int	i_arg;

	r_arg = ft_is_double(argv[2]);
	i_arg = ft_is_double(argv[3]);
	if (r_arg == 0 || i_arg == 0)
		usage_input_and_exit(2);
	if (r_arg == 1)
		lst->r_julia = (long double)ft_atoi(argv[2]);
	else if (r_arg == 2)
		lst->r_julia = ft_atold(argv[2]);
	if (i_arg == 1)
		lst->i_julia = (long double)ft_atoi(argv[3]);
	else if (i_arg == 2)
		lst->i_julia = ft_atold(argv[3]);
	return (2);
}

int	input_valid(int argc, char **argv, t_fractal *lst)
{
	if (argc == 1)
		usage_input_and_exit(1);
	if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
	{
		if (argc != 2)
			usage_input_and_exit(1);
		else
			lst->name = ft_strdup("Mandelbrot");
	}
	if (ft_strncmp(argv[1], "Julia", 6) == 0 && argc == 4)
		return (julia_valid(argv, &lst));
	else
		usage_input_and_exit(1);
	return (0);
}
