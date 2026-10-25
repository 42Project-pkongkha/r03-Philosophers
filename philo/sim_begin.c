/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_begin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:39:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 23:57:00 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "sim.h"

#include "philo.h"

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

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
	size_t							idx;
	struct s_philo_routine_params	*params;
	struct s_table					*tbl = &sim->table;

	pthread_mutex_lock(&sim->running.lock);
	idx = 0;
	while (idx < tbl->philo_cnt)
	{
		params = malloc(sizeof(*params));
		if (!params)
		{
			pthread_mutex_unlock(&sim->running.lock);
			join_threads(tbl->philo_thread_ids, idx);
			return (-ENOMEM);
		}
		*params = (struct s_philo_routine_params){
			.philo_num = idx,
			.sim = sim,
		};
		if (pthread_create(&tbl->philo_thread_ids[idx], NULL, philo_routine, params))
		{
			free(params);
			pthread_mutex_unlock(&sim->running.lock);
			join_threads(tbl->philo_thread_ids, idx);
			return (-EAGAIN);
		}
		++idx;
	}
	sim->running.value = true;
	gettimeofday(&sim->time_begin, NULL);
	idx = 0;
	while (idx < tbl->philo_cnt)
		guarded_timeval_write(&tbl->philos[idx++].last_eat, sim->time_begin);
	pthread_mutex_unlock(&sim->running.lock);
	return (0);
}
