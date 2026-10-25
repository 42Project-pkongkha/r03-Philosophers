/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:35:29 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/26 00:01:27 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "philo.h"
#include "sim.h"
#include "usage.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

bool	is_philo_died(struct timeval currtime, struct timeval die_after) {
	if (currtime.tv_sec > die_after.tv_sec
		|| (currtime.tv_sec == die_after.tv_sec
			&& currtime.tv_usec > die_after.tv_usec))
	{
		return (true);
	}
	return (false);
}

int	sim_check(struct s_sim *sim)
{
	struct s_table *const	tbl = &sim->table;
	struct s_rules *const	rules = &sim->rules;
	struct timeval			currtime;
	struct timeval			die_after;
	size_t					idx;

	if (rules->cnt_eat_to_success >= 0)
	{
		idx = 0;
		while (idx < tbl->philo_cnt)
		{
			if (guarded_ssize_t_read(&tbl->philos[idx].cnt_eaten)
					< rules->cnt_eat_to_success)
				break;
			++idx;
		}
		if (idx == tbl->philo_cnt)
			return (1);
	}
	idx = 0;
	gettimeofday(&currtime, NULL);
	while (idx < tbl->philo_cnt)
	{
		if (!(rules->cnt_eat_to_success != -1 &&
				guarded_ssize_t_read(&tbl->philos[idx].cnt_eaten)
					== rules->cnt_eat_to_success))
		{
			die_after = guarded_timeval_read(&tbl->philos[idx].last_eat);
			die_after.tv_usec += rules->time_die.tv_usec;
			die_after.tv_sec += rules->time_die.tv_sec
				+ die_after.tv_usec / 1000000;
			die_after.tv_usec %= 1000000;
			if (is_philo_died(currtime, die_after))
			{
				guarded_bool_write(&sim->running, false);
				sim_print_philo_state(sim, idx, PHILO_DIED);
				return (-1);
			}
		}
		++idx;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	struct s_sim	sim;

	if (argc != 5 && argc != 6)
	{
		usage(argv[0]);
		return (EXIT_FAILURE);
	}
	if (sim_init(&sim, argc, argv))
		return (EXIT_FAILURE);
	if (sim_begin(&sim))
	{
		sim_destroy(&sim);
		return (EXIT_FAILURE);
	}
	while (!sim_check(&sim))
		;
	sim_stop(&sim);
	sim_destroy(&sim);
}
