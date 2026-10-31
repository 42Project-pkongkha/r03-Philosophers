/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_bool_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:12 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:45:03 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline bool	guarded_bool_read(struct s_guarded_bool *g_bool)
{
	bool	value;

	pthread_mutex_lock(&g_bool->lock);
	value = g_bool->value;
	pthread_mutex_unlock(&g_bool->lock);
	return (value);
}
