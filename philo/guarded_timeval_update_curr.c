/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_timeval_update_curr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 22:55:28 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 22:57:50 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

#include <pthread.h>
#include <sys/time.h>

void	guarded_timeval_update_curr(struct s_guarded_timeval *guarded_tv)
{
	pthread_mutex_lock(&guarded_tv->lock);
	gettimeofday(&guarded_tv->tv, NULL);
	pthread_mutex_unlock(&guarded_tv->lock);
}
