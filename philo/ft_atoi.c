/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 02:37:59 by pkongkha          #+#    #+#             */
/*   Updated: 2026/01/04 01:40:28 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	neg;

	while (ft_isspace(*nptr))
		++nptr;
	neg = 1 - (2 * (*nptr == '-'));
	if (*nptr == '-' || *nptr == '+')
		++nptr;
	num = 0;
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0') * neg;
		++nptr;
	}
	return (num);
}
