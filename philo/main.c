/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:35:29 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 18:24:49 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "philo.h"
#include "philo_types.h"
#include "sim.h"
#include "usage.h"

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

static int	sim_check(struct s_sim *sim)
{
	struct s_rules *const	rules = &sim->rules;
	size_t					idx;
	t_mseconds 				eat_deadline;

	if (rules->cnt_eat_to_success >= 0)
	{
		idx = 0;
		while (idx < rules->philo_cnt)
		{
			if (guarded_ssize_read(&sim->philos[idx].cnt_eaten)
					< rules->cnt_eat_to_success)
				break;
			++idx;
		}
		if (idx == rules->philo_cnt)
			return (1);
	}
	if (sim_getelapsedtime_ms() < rules->time_die)
		eat_deadline = 0;
	else
		eat_deadline = sim_getelapsedtime_ms() - rules->time_die;
	idx = 0;
	while (idx < rules->philo_cnt)
	{
		if (!(rules->cnt_eat_to_success != -1 &&
				guarded_ssize_read(&sim->philos[idx].cnt_eaten)
					== rules->cnt_eat_to_success))
		{
			if (guarded_mseconds_read(&sim->philos[idx].last_eat) < eat_deadline)
			{
				guarded_bool_write(&sim->running, false);
				sim_print_philo_state(&sim->running, idx, PHILO_DIED);
				return (-1);
			}
		}
		++idx;
	}
	return (0);
}

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
