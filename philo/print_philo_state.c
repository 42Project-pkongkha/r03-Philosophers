/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:33:38 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/04 14:09:44 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

#include "philo.h"
#include "sim.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>

int	print_philo_state(
		struct s_sim *sim,
		size_t philo_num,
		enum e_philo_state state)
{
	const char *const	state_str[] = {
	[PHILO_TAKEN_FORK] = "has taken a fork",
	[PHILO_EATING] = "is eating",
	[PHILO_SLEEPING] = "is sleeping",
	[PHILO_THINKING] = "is thinking",
	[PHILO_DIED] = "died",
	};

	pthread_mutex_lock(&sim->running.lock);
	if (state != PHILO_DIED && !sim->running.value)
	{
		pthread_mutex_unlock(&sim->running.lock);
		return (ECANCELED);
	}
	printf("%ld %zu %s\n",
		gettime_ms() - sim->time_start,
		philo_num + 1,
		state_str[state]);
	pthread_mutex_unlock(&sim->running.lock);
	return (0);
}
