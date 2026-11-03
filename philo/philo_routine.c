/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:38:58 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 15:21:45 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"
#include "philo.h"

#include "sim.h"

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int	philo_eat(
		struct s_philo *self
) {
	int	ret;

	guarded_mseconds_write(&self->last_eat, gettime_ms());
	ret = print_philo_state(self->sim, self->num, PHILO_EATING);
	if (ret)
		return (ret);
	pthread_mutex_lock(&self->cnt_eaten.lock);
	++self->cnt_eaten.value;
	pthread_mutex_unlock(&self->cnt_eaten.lock);
	usleep(self->rules->time_eat * 1000);
	return (0);
}

static void	wait_before_next_eat(struct s_philo *self)
{
	const t_mseconds	elapsed_from_last_eat
		= gettime_ms() - guarded_mseconds_read(&self->last_eat);
	t_mseconds			time_left;

	if (self->rules->time_die <= elapsed_from_last_eat + 5)
		return ;
	time_left = self->rules->time_die - elapsed_from_last_eat;
	usleep(time_left * 1000 - 5000);
}

static void	mutex_unlock_then_pthr_exit(
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
		struct s_philo *self
) {
	const struct s_rules	*rules = self->rules;

	while (1)
	{
		pthread_mutex_lock(self->forks[0]);
		if (print_philo_state(self->sim, self->num, PHILO_TAKEN_FORK))
			mutex_unlock_then_pthr_exit(self->forks[0], NULL);
		pthread_mutex_lock(self->forks[1]);
		if (philo_eat(self))
			mutex_unlock_then_pthr_exit(self->forks[0], self->forks[1]);
		pthread_mutex_unlock(self->forks[1]);
		pthread_mutex_unlock(self->forks[0]);
		if (rules->cnt_eat_to_success > 0
			&& (guarded_int_read(&self->cnt_eaten)
				>= rules->cnt_eat_to_success))
			pthread_exit(NULL);
		if (print_philo_state(self->sim, self->num, PHILO_SLEEPING))
			pthread_exit(NULL);
		usleep(rules->time_sleep * 1000);
		if (print_philo_state(self->sim, self->num, PHILO_THINKING))
			pthread_exit(NULL);
		wait_before_next_eat(self);
	}
}

void	*philo_routine(void *arg)
{
	struct s_philo	*self;

	self = ((struct s_philo *)arg);
	while (gettime_ms() < self->sim->time_start)
		usleep(200);
	if (self->rules->philo_cnt == 1)
		philo_is_so_alone(self->sim, self->num, self->forks[0]);
	if (guarded_bool_read(&self->sim->running))
	{
		if (self->num % 2 == 0)
			usleep(2000);
		philo_routine_loop(self);
	}
	pthread_exit(NULL);
}
