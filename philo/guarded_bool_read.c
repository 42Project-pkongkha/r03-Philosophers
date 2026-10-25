/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_bool_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:12 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:53:21 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

bool	guarded_bool_read(struct s_guarded_bool *var)
{
	bool	value;

	pthread_mutex_lock(&var->lock);
	value = var->value;
	pthread_mutex_unlock(&var->lock);
	return (value);
}
