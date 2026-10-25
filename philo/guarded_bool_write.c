/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_bool_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:52:55 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 19:53:06 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guarded_type.h"

void	guarded_bool_write(struct s_guarded_bool *var, bool value)
{
	pthread_mutex_lock(&var->lock);
	var->value = value;
	pthread_mutex_unlock(&var->lock);
}
