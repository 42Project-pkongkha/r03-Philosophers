/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:17:59 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 01:38:19 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_H
# define SIM_H

# include "guarded_type.h"
# include "philo_types.h"

# include <pthread.h>

struct s_rules
{
	size_t		philo_cnt;
	int			cnt_eat_to_success;
	t_mseconds	time_die;
	t_mseconds	time_eat;
	t_mseconds	time_sleep;
};

struct s_sim
{
	struct s_guarded_bool	running;
	t_mseconds				time_start;
	struct s_rules			rules;
	struct s_philo			*philos;
	pthread_t				*philo_thread_ids;
	struct s_guarded_bool	*forks;
};

int			sim_init(struct s_sim *sim, int argc, char *argv[]);
int			sim_begin(struct s_sim *sim);
int			sim_check(struct s_sim *sim);
void		sim_stop(struct s_sim *sim);
void		sim_destroy(struct s_sim *sim);
int			print_philo_state(
				struct s_sim *sim,
				size_t philo_num,
				enum e_philo_state state);
#endif
