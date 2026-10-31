/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_ssize_write.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:48:17 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline void	guarded_ssize_write(struct s_guarded_ssize *g_ssize, ssize_t value)
{
	pthread_mutex_lock(&g_ssize->lock);
	g_ssize->value = value;
	pthread_mutex_unlock(&g_ssize->lock);
}
