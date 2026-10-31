/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_mseconds_read.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 19:28:47 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:25:24 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

#include <pthread.h>

t_mseconds	guarded_mseconds_read(struct s_guarded_mseconds *g_msec)
{
	t_mseconds	msec;

	pthread_mutex_lock(&g_msec->lock);
	msec = g_msec->msec;
	pthread_mutex_unlock(&g_msec->lock);
	return (msec);
}
