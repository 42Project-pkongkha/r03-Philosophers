/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:40:52 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 23:50:19 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"

#include <stdlib.h>
#include <pthread.h>

void	sim_destroy(struct s_sim *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->table.philo_cnt)
	{
		pthread_mutex_destroy(&sim->table.forks[i]);
		pthread_mutex_destroy(&sim->table.philos[i].cnt_eaten.lock);
		pthread_mutex_destroy(&sim->table.philos[i].last_eat.lock);
		++i;
	}
	pthread_mutex_destroy(&sim->running.lock);
	free(sim->table.philo_thread_ids);
	free(sim->table.philos);
	free(sim->table.forks);
}
