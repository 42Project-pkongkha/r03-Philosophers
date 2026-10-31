/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:40:52 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 15:52:51 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"
#include "philo.h"

#include <stdlib.h>
#include <pthread.h>

void	sim_destroy(struct s_sim *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->rules.philo_cnt)
	{
		pthread_mutex_destroy(&sim->forks[i].lock);
		pthread_mutex_destroy(&sim->philos[i].cnt_eaten.lock);
		pthread_mutex_destroy(&sim->philos[i].last_eat.lock);
		++i;
	}
	pthread_mutex_destroy(&sim->running.lock);
	free(sim->philo_thread_ids);
	free(sim->philos);
	free(sim->forks);
}
