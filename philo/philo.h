/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:32:02 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/16 18:29:40 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "guarded_type.h"

# include <unistd.h>

struct s_philo
{
	struct s_guarded_ssize_t	cnt_eaten;
	struct s_guarded_timeval	last_eat;
};

struct s_philo_routine_params
{
	size_t			philo_num;
	struct s_sim	*sim;
};

enum e_philo_state
{
	PHILO_TAKEN_FORK,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DIED,
};

void	*philo_routine(void *arg);
#endif
