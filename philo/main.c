/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:35:29 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 19:11:15 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"
#include "usage.h"

#include "libft.h"

#include <stdlib.h>

static int	is_all_digits(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		++s;
	}
	return (1);
}

int	is_args_valid(int argc, char **argv)
{
	if (!is_all_digits(argv[1])
		|| !is_all_digits(argv[2])
		|| !is_all_digits(argv[3])
		|| !is_all_digits(argv[4]))
		return (0);
	if (argc == 6)
		return (is_all_digits(argv[5]));
	return (1);
}

int	main(int argc, char *argv[])
{
	struct s_sim	sim;

	if ((argc != 5 && argc != 6) || !is_args_valid(argc, argv))
	{
		usage(argv[0]);
		return (EXIT_FAILURE);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (EXIT_SUCCESS);
	if (sim_init(&sim, argc, argv))
		return (EXIT_FAILURE);
	if (sim_begin(&sim))
	{
		sim_destroy(&sim);
		return (EXIT_FAILURE);
	}
	while (!sim_check(&sim))
		usleep(20);
	sim_stop(&sim);
	sim_destroy(&sim);
}
