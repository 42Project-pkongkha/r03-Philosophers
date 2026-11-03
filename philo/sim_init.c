/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:40:37 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 15:12:08 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "philo.h"
#include "sim.h"

#include "usage.h"
#include "libft.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

static int	rules_init(struct s_rules *rules, int argc, char *argv[])
{
	*rules = (struct s_rules){
		.philo_cnt = ft_atoi(argv[1]),
		.time_die = ft_atoi(argv[2]),
		.time_eat = ft_atoi(argv[3]),
		.time_sleep = ft_atoi(argv[4]),
	};
	if (argc == 6)
		rules->cnt_eat_to_success = ft_atoi(argv[5]);
	else
		rules->cnt_eat_to_success = -1;
	return (0);
}

static int	philos_init(
		struct s_philo *philos,
		struct s_sim *sim,
		struct s_rules *rules,
		pthread_mutex_t *all_fork
) {
	size_t	idx;

	idx = 0;
	while (idx < rules->philo_cnt)
	{
		philos[idx].sim = sim;
		philos[idx].rules = rules;
		philos[idx].num = idx;
		pthread_mutex_init(&philos[idx].cnt_eaten.lock, NULL);
		pthread_mutex_init(&philos[idx].last_eat.lock, NULL);
		if (idx == rules->philo_cnt - 1)
			philos[idx].forks[0] = &all_fork[0];
		else
			philos[idx].forks[0] = &all_fork[idx + (idx % 2)];
		if (rules->philo_cnt % 2 == 1
			&& idx == rules->philo_cnt - 1)
			philos[idx].forks[1] = &all_fork[idx];
		else
			philos[idx].forks[1] = &all_fork[idx + (idx % 2 == 0)];
		++idx;
	}
	return (0);
}

static void	forks_init(pthread_mutex_t *forks, size_t n)
{
	while (n)
	{
		pthread_mutex_init(forks, NULL);
		++forks;
		--n;
	}
}

// NOLINTBEGIN(misc-non-copyable-objects)
int	sim_init(struct s_sim *sim, int argc, char *argv[])
{
	if (rules_init(&sim->rules, argc, argv))
	{
		usage(argv[0]);
		return (-1);
	}
	sim->philos = malloc(sim->rules.philo_cnt * sizeof(*sim->philos));
	sim->philo_thread_ids = malloc(sim->rules.philo_cnt
			* sizeof(*sim->philo_thread_ids));
	sim->forks = malloc(sim->rules.philo_cnt * sizeof(*sim->forks));
	philos_init(sim->philos, sim, &sim->rules, sim->forks);
	forks_init(sim->forks, sim->rules.philo_cnt);
	sim->running.value = false;
	pthread_mutex_init(&sim->running.lock, NULL);
	return (0);
}
// NOLINTEND(misc-non-copyable-objects)
