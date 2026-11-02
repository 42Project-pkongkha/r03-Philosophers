/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 17:32:22 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/03 01:36:56 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo_types.h"

#include <unistd.h>
#include <sys/time.h>

t_mseconds	gettime_ms(void)
{
	struct timeval	currtime;

	gettimeofday(&currtime, NULL);
	return (currtime.tv_sec * 1000 + currtime.tv_usec / 1000);
}
