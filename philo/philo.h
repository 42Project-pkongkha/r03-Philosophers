/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:32:02 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 15:17:54 by pkongkha         ###   ########.fr       */
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
	pthread_mutex_t				*forks[2];
	size_t						num;
	struct s_guarded_int		cnt_eaten;
	struct s_guarded_mseconds	last_eat;
};

t_mseconds	gettime_ms(void);
void		*philo_routine(void *arg);
void		philo_is_so_alone(
				struct s_sim *sim,
				size_t philo_num,
				pthread_mutex_t *fork);
#endif
