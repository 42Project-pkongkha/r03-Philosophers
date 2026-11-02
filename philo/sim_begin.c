/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_begin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:39:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 01:44:36 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "sim.h"

#include "philo.h"

#include <asm-generic/errno.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void	join_threads(pthread_t *threads, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		pthread_join(threads[idx], NULL);
		++idx;
	}
}

static void	sim_begin_philo_init(struct s_sim *sim)
{
	size_t	idx;

	idx = 0;
	while (idx < sim->rules.philo_cnt)
	{
		sim->philos[idx].cnt_eaten.value = 0;
		sim->philos[idx].last_eat.msec = 0;
		++idx;
	}
}

static int	sim_begin_philo_spawn(struct s_sim *sim)
{
	size_t					idx;
	struct s_rules *const	rules = &sim->rules;

	idx = 0;
	while (idx < rules->philo_cnt)
	{
		sim->philos[idx].last_eat.msec = sim->time_start;
		if (pthread_create(&sim->philo_thread_ids[idx], NULL, philo_routine,
				&sim->philos[idx]))
		{
			pthread_mutex_unlock(&sim->running.lock);
			join_threads(sim->philo_thread_ids, idx);
			printf("sim_begin: cannot create new thread\n");
			return (-EAGAIN);
		}
		++idx;
	}
	return (0);
}

int	sim_begin(struct s_sim *sim)
{
	int	rc;

	pthread_mutex_lock(&sim->running.lock);
	sim_begin_philo_init(sim);
	sim->time_start = gettime_ms() + 5 * sim->rules.philo_cnt;
	rc = sim_begin_philo_spawn(sim);
	if (rc)
		return (rc);
	if (gettime_ms() > sim->time_start)
	{
		printf("sim_begin: uses too much time to create thread\n");
		return (-ETIMEDOUT);
	}
	sim->running.value = true;
	pthread_mutex_unlock(&sim->running.lock);
	return (0);
}
