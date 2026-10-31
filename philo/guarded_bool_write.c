/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_bool_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:52:55 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 14:45:11 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline void	guarded_bool_write(struct s_guarded_bool *g_bool, bool value)
{
	pthread_mutex_lock(&g_bool->lock);
	g_bool->value = value;
	pthread_mutex_unlock(&g_bool->lock);
}
