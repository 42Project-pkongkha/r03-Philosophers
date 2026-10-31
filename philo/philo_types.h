/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 19:39:18 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:01:58 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include <inttypes.h>

typedef uint64_t	t_mseconds;

enum e_philo_state
{
	PHILO_TAKEN_FORK,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DIED,
};

#endif
