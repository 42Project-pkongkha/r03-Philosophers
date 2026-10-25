/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_print_philo_state.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:33:38 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:46:38 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "sim.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

int	sim_print_philo_state(struct s_sim *sim, size_t philo_num,
		enum e_philo_state state)
{
	struct timeval		tv_curr;
	const char *const	state_str[] = {
	[PHILO_TAKEN_FORK] = "has taken a fork",
	[PHILO_EATING] = "is eating",
	[PHILO_SLEEPING] = "is sleeping",
	[PHILO_THINKING] = "is thinking",
	[PHILO_DIED] = "died",
	};

	gettimeofday(&tv_curr, NULL);
	pthread_mutex_lock(&sim->running.lock);
	if (state != PHILO_DIED && !sim->running.value)
	{
		pthread_mutex_unlock(&sim->running.lock);
		return (ECANCELED);
	}
	printf("%ld %zu %s\n",
		(tv_curr.tv_sec - sim->time_begin.tv_sec) * 1000
		+ (tv_curr.tv_usec - sim->time_begin.tv_usec) / 1000,
		philo_num,
		state_str[state]);
	pthread_mutex_unlock(&sim->running.lock);
	return (0);
}
