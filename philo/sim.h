/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:17:59 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 22:06:54 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_H
# define SIM_H

# include "philo.h"

# include <sys/time.h>

struct s_rules
{
	ssize_t			cnt_eat_to_success;
	struct timeval	time_die;
	useconds_t		time_eat;
	useconds_t		time_sleep;
};

struct s_table
{
	size_t				philo_cnt;
	struct s_philo		*philos;
	pthread_t			*philo_thread_ids;
	pthread_mutex_t		*forks;
};

struct s_sim
{
	struct s_guarded_bool	running;
	struct timeval			time_begin;
	struct s_rules			rules;
	struct s_table			table;
};

int		sim_init(struct s_sim *sim, int argc, char *argv[]);
int		sim_begin(struct s_sim *sim);
void	sim_stop(struct s_sim *sim);
void	sim_destroy(struct s_sim *sim);
int		sim_print_philo_state(struct s_sim *sim, size_t philo_num,
			enum e_philo_state state);
#endif
