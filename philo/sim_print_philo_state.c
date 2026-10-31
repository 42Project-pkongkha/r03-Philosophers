/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_print_philo_state.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:33:38 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:53:41 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "sim.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>

int	sim_print_philo_state(
		struct s_guarded_bool *running,
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

	pthread_mutex_lock(&running->lock);
	if (state != PHILO_DIED && !running->value)
	{
		pthread_mutex_unlock(&running->lock);
		return (ECANCELED);
	}
	printf("%ld %zu %s\n",
		sim_getelapsedtime_ms(),
		philo_num,
		state_str[state]);
	pthread_mutex_unlock(&running->lock);
	return (0);
}
