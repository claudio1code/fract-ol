/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:30:00 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/21 17:49:53 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *nptr)
{
	double	divider;
	double	result;
	int		signal;
	int		i;

	if (ft_is_double(nptr) == 0)
		return (0);
	divider = 1.0;
	signal = ft_signal(nptr);
	i = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		divider /= 10.0;
		result += (nptr[i] - '0') * divider;
		i++;
	}
	return (result * signal);
}
