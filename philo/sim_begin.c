/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_begin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:39:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 18:31:03 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "sim.h"

#include "philo.h"

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

int	sim_begin(struct s_sim *sim)
{
	size_t			idx;
	struct s_rules	*rules = &sim->rules;

	pthread_mutex_lock(&sim->running.lock);
	idx = 0;
	while (idx < rules->philo_cnt)
	{
		if (pthread_create(&sim->philo_thread_ids[idx], NULL, philo_routine, &sim->philos[idx]))
		{
			pthread_mutex_unlock(&sim->running.lock);
			join_threads(sim->philo_thread_ids, idx);
			printf("sim_begin: cannot create new thread\n");
			return (-EAGAIN);
		}
		++idx;
	}
	sim->running.value = true;
	idx = 0;
	while (idx < rules->philo_cnt)
	{
		sim->philos[idx].cnt_eaten.value = 0;
		sim->philos[idx].last_eat.msec = 0;
		++idx;
	}
	sim_getelapsedtime_ms();
	pthread_mutex_unlock(&sim->running.lock);
	return (0);
}
