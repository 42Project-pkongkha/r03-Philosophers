/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_stop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:39:58 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 22:25:17 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"

#include <stdbool.h>
#include <pthread.h>
#include <stddef.h>

void	sim_stop(struct s_sim *sim)
{
	size_t	i;

	pthread_mutex_lock(&sim->running.lock);
	sim->running.value = false;
	pthread_mutex_unlock(&sim->running.lock);
	i = 0;
	while (i < sim->table.philo_cnt)
	{
		pthread_join(sim->table.philo_thread_ids[i], NULL);
		++i;
	}
}
