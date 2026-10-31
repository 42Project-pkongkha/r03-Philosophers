/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 19:00:39 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 19:07:22 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"
#include "philo.h"

static int	sim_check_full(struct s_sim *sim)
{
	size_t					idx;
	struct s_rules *const	rules = &sim->rules;

	if (rules->cnt_eat_to_success >= 0)
	{
		idx = 0;
		while (idx < rules->philo_cnt)
		{
			if (guarded_ssize_read(&sim->philos[idx].cnt_eaten)
				< rules->cnt_eat_to_success)
				break ;
			++idx;
		}
		if (idx == rules->philo_cnt)
			return (1);
	}
	return (0);
}

static int	sim_check_died(struct s_sim *sim)
{
	struct s_rules *const	rules = &sim->rules;
	size_t					idx;
	t_mseconds				eat_deadline;

	if (sim_getelapsedtime_ms() < rules->time_die)
		return (0);
	eat_deadline = sim_getelapsedtime_ms() - rules->time_die;
	idx = 0;
	while (idx < rules->philo_cnt)
	{
		if (!(rules->cnt_eat_to_success != -1
				&& guarded_ssize_read(&sim->philos[idx].cnt_eaten)
				== rules->cnt_eat_to_success))
		{
			if (guarded_mseconds_read(&sim->philos[idx].last_eat)
				< eat_deadline)
			{
				guarded_bool_write(&sim->running, false);
				sim_print_philo_state(&sim->running, idx, PHILO_DIED);
				return (1);
			}
		}
		++idx;
	}
	return (0);
}

int	sim_check(struct s_sim *sim)
{
	int	rc;

	rc = sim_check_full(sim);
	if (rc)
		return (rc);
	rc = sim_check_died(sim);
	if (rc)
		return (rc);
	return (0);
}
