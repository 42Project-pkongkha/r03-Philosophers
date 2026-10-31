/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_ssize_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:57 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:48:09 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline ssize_t	guarded_ssize_read(struct s_guarded_ssize *g_ssize)
{
	ssize_t	value;

	pthread_mutex_lock(&g_ssize->lock);
	value = g_ssize->value;
	pthread_mutex_unlock(&g_ssize->lock);
	return (value);
}
