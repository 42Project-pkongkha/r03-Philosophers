/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_ssize_t_read.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:57 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:54:17 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

ssize_t	guarded_ssize_t_read(struct s_guarded_ssize_t *var)
{
	ssize_t	value;

	pthread_mutex_lock(&var->lock);
	value = var->value;
	pthread_mutex_unlock(&var->lock);
	return (value);
}
