/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_is_so_alone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:16:15 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 15:18:18 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>

void	philo_is_so_alone(
		struct s_sim *sim,
		size_t philo_num,
		pthread_mutex_t *fork
) {
	pthread_mutex_lock(fork);
	print_philo_state(sim, philo_num, PHILO_TAKEN_FORK);
	usleep(sim->rules.time_die - (gettime_ms() - sim->time_start));
	pthread_mutex_unlock(fork);
	pthread_exit(NULL);
}
