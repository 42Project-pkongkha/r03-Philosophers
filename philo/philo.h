/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:32:02 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 01:38:33 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "guarded_type.h"
# include "sim.h"

# include <stdint.h>
# include <unistd.h>

struct s_philo
{
	struct s_sim				*sim;
	struct s_rules				*rules;
	struct s_guarded_bool		*forks[2];
	size_t						num;
	struct s_guarded_int		cnt_eaten;
	struct s_guarded_mseconds	last_eat;
};

t_mseconds	gettime_ms(void);
void		fork_take(struct s_guarded_bool *fork);
void		fork_return(struct s_guarded_bool *fork);
void		fork_return_then_pthr_exit(
				struct s_guarded_bool *fk1,
				struct s_guarded_bool *fk2
				);
void		*philo_routine(void *arg);
#endif
