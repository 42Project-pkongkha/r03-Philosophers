/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_mseconds_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 19:28:47 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/30 19:36:36 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

#include <pthread.h>

void	guarded_mseconds_write(
		struct s_guarded_mseconds *g_msec,
		t_mseconds msec
) {
	pthread_mutex_lock(&g_msec->lock);
	g_msec->msec = msec;
	pthread_mutex_unlock(&g_msec->lock);
}
