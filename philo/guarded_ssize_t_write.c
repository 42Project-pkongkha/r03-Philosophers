/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_ssize_t_write.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:53:30 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:53:40 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

void	guarded_ssize_t_write(struct s_guarded_ssize_t *var, ssize_t value)
{
	pthread_mutex_lock(&var->lock);
	var->value = value;
	pthread_mutex_unlock(&var->lock);
}
