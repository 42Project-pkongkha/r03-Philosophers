/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 18:58:11 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 19:04:48 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This is a workaround since pthread_mutex_lock does not ensure FIFO
// ordering
void	fork_take(struct s_guarded_bool *fork)
{
	while (guarded_bool_read(fork) != true)
		usleep(20);
	guarded_bool_write(fork, false);
}

void	fork_return(struct s_guarded_bool *fork)
{
	guarded_bool_write(fork, true);
}

void	fork_return_then_pthr_exit(
		struct s_guarded_bool *fk1,
		struct s_guarded_bool *fk2
) {
	if (fk1)
		fork_return(fk1);
	if (fk2)
		fork_return(fk2);
}
