/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:38:58 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/26 00:03:02 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "philo.h"

#include "sim.h"

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int	philo_eat(struct s_sim *sim, size_t philo_num)
{
	struct s_philo *const	philo = &sim->table.philos[philo_num];
	int						ret;

	guarded_timeval_update_curr(&philo->last_eat);
	ret = sim_print_philo_state(sim, philo_num, PHILO_EATING);
	if (ret)
		return (ret);
	usleep(sim->rules.time_eat);
	pthread_mutex_lock(&philo->cnt_eaten.lock);
	++philo->cnt_eaten.value;
	pthread_mutex_unlock(&philo->cnt_eaten.lock);
	return (0);
}

static int	unlock_mutexes_and_pthread_exit(
		pthread_mutex_t *lock1,
		pthread_mutex_t *lock2
) {
	if (lock1)
		pthread_mutex_unlock(lock1);
	if (lock2)
		pthread_mutex_unlock(lock2);
	pthread_exit(NULL);
}

static void	philo_routine_loop(
		struct s_sim *sim,
		size_t philo_num,
		pthread_mutex_t *forks[2]
) {
	struct s_guarded_ssize_t	*cnt_eaten;

	cnt_eaten = &sim->table.philos[philo_num].cnt_eaten;
	while (1)
	{
		pthread_mutex_lock(forks[0]);
		if (sim_print_philo_state(sim, philo_num, PHILO_TAKEN_FORK))
			unlock_mutexes_and_pthread_exit(forks[0], NULL);
		pthread_mutex_lock(forks[1]);
		if (philo_eat(sim, philo_num))
			unlock_mutexes_and_pthread_exit(forks[0], forks[1]);
		pthread_mutex_unlock(forks[1]);
		pthread_mutex_unlock(forks[0]);
		if (sim->rules.cnt_eat_to_success > 0
				&& (guarded_ssize_t_read(cnt_eaten)
					>= sim->rules.cnt_eat_to_success))
			pthread_exit(NULL);
		if (sim_print_philo_state(sim, philo_num, PHILO_SLEEPING))
			pthread_exit(NULL);
		usleep(sim->rules.time_sleep);
		if (sim_print_philo_state(sim, philo_num, PHILO_THINKING))
			pthread_exit(NULL);
	}
}

void	*philo_routine(void *arg)
{
	const size_t		philo_num
		= ((struct s_philo_routine_params*)arg)->philo_num;
	struct s_sim *const	sim
		= ((struct s_philo_routine_params*)arg)->sim;
	pthread_mutex_t		*all_fork = sim->table.forks;
	pthread_mutex_t		*forks[2];

	free(arg);
	forks[0] = &all_fork[philo_num - (philo_num % 2)];
	if (sim->table.philo_cnt % 2 == 1
			&& philo_num == sim->table.philo_cnt - 1)
		forks[1] = &all_fork[0];
	else
		forks[1] = &all_fork[philo_num + (philo_num % 2 == 0)];
	if (guarded_bool_read(&sim->running))
		philo_routine_loop(sim, philo_num, forks);
	pthread_exit(NULL);
}
