/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 19:00:39 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 00:27:06 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_types.h"
#include "sim.h"
#include "philo.h"
#include <pthread.h>

static bool	is_cond_end(
		struct s_sim *sim,
		t_mseconds eat_deadline,
		bool all_ate_enough
) {
	size_t	idx;

	idx = 0;
	while (idx < sim->rules.philo_cnt)
	{
		if (guarded_int_read(&sim->philos[idx].cnt_eaten)
			!= sim->rules.cnt_eat_to_success)
		{
			all_ate_enough = false;
			pthread_mutex_lock(&sim->philos[idx].last_eat.lock);
			if (sim->philos[idx].last_eat.msec < eat_deadline)
			{
				guarded_bool_write(&sim->running, false);
				pthread_mutex_unlock(&sim->philos[idx].last_eat.lock);
				print_philo_state(sim, idx, PHILO_DIED);
				return (1);
			}
			pthread_mutex_unlock(&sim->philos[idx].last_eat.lock);
		}
		++idx;
	}
	return (all_ate_enough);
}

// NOLINTBEGIN(readability-inconsistent-ifelse-braces)
int	sim_check(struct s_sim *sim)
{
	struct s_rules *const	rules = &sim->rules;
	const t_mseconds		now = gettime_ms();
	t_mseconds				eat_deadline;
	bool					all_ate_enough;

	if (now < sim->time_start
		&& now - sim->time_start < rules->time_die)
		return (0);
	eat_deadline = now - rules->time_die;
	all_ate_enough = rules->cnt_eat_to_success != -1;
	return (is_cond_end(sim, eat_deadline, all_ate_enough));
}
// NOLINTEND(readability-inconsistent-ifelse-braces)
