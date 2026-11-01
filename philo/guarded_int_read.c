/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_int_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:57 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/01 21:30:25 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

inline int	guarded_int_read(struct s_guarded_int *g_int)
{
	int	value;

	pthread_mutex_lock(&g_int->lock);
	value = g_int->value;
	pthread_mutex_unlock(&g_int->lock);
	return (value);
}
