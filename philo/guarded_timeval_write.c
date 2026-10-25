/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_timeval_write.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:51:25 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:51:33 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

void	guarded_timeval_write(struct s_guarded_timeval *var, struct timeval value)
{
	pthread_mutex_lock(&var->lock);
	var->tv = value;
	pthread_mutex_unlock(&var->lock);
}

