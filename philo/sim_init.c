/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:40:37 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 23:08:57 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"

#include "usage.h"
#include "libft.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int	parseargs(struct s_sim *sim, int argc, char *argv[])
{
	sim->table.philo_cnt = ft_atoi(argv[1]);
	sim->rules = (struct s_rules){
		.time_die = {
		.tv_sec = ft_atoi(argv[2]) / 1000,
		.tv_usec = (useconds_t)(ft_atoi(argv[2]) % 1000 * 1000),
	},
		.time_eat = ft_atoi(argv[3]) * 1000,
		.time_sleep = ft_atoi(argv[4]) * 1000,
	};
	if (argc < 6)
		sim->rules.cnt_eat_to_success = -1;
	else
		sim->rules.cnt_eat_to_success = ft_atoi(argv[5]);
	return (0);
}

static void	mutexes_init(pthread_mutex_t *mutexes, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
		pthread_mutex_init(&mutexes[idx++], NULL);
}

static void	philo_init(struct s_philo *philos, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		philos->cnt_eaten.value = 0;
		pthread_mutex_init(&philos->cnt_eaten.lock, NULL);
		philos->last_eat.tv = (struct timeval){
			.tv_sec = 0,
			.tv_usec = 0,
		};
		pthread_mutex_init(&philos->last_eat.lock, NULL);
		++philos;
		++idx;
	}
}

// NOLINTBEGIN(misc-non-copyable-objects)
static int	table_init(struct s_table *table)
{
	table->philos = malloc(table->philo_cnt * sizeof(*table->philos));
	if (!table->philos)
		return (ENOMEM);
	table->philo_thread_ids =
		malloc(table->philo_cnt * sizeof(*table->philo_thread_ids));
	if (!table->philo_thread_ids)
	{
		free(table->philos);
		return (ENOMEM);
	}
	table->forks = malloc(table->philo_cnt * sizeof(*table->forks));
	if (!table->forks)
	{
		free(table->philos);
		free(table->philo_thread_ids);
		return (ENOMEM);
	}
	philo_init(table->philos, table->philo_cnt);
	mutexes_init(table->forks, table->philo_cnt);
	return (0);
}
// NOLINTEND(misc-non-copyable-objects)

int	sim_init(struct s_sim *sim, int argc, char *argv[])
{
	int	rc;

	if (parseargs(sim, argc, argv))
	{
		usage(argv[0]);
		return (-1);
	}
	rc = table_init(&sim->table);
	if (rc)
		return (rc);
	pthread_mutex_init(&sim->running.lock, NULL);
	sim->running.value = false;
	return (0);
}
