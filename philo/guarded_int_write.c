/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_int_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/01 21:28:11 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline void	guarded_int_write(struct s_guarded_int *g_int, int value)
{
	pthread_mutex_lock(&g_int->lock);
	g_int->value = value;
	pthread_mutex_unlock(&g_int->lock);
}
