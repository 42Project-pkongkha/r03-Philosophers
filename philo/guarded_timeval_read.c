/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_timeval_read.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:51:48 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:52:00 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

struct timeval	guarded_timeval_read(struct s_guarded_timeval *var)
{
	struct timeval	value;

	pthread_mutex_lock(&var->lock);
	value = var->tv;
	pthread_mutex_unlock(&var->lock);
	return (value);
}
