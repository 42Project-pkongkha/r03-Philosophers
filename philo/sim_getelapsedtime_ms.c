/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_getelapsedtime_ms.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 17:32:22 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/30 18:26:43 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"

#include <sys/time.h>

t_mseconds	sim_getelapsedtime_ms(void)
{
	static bool				initialized;
	static struct timeval	starttime;
	struct timeval			currtime;

	gettimeofday(&currtime, NULL);
	if (!initialized)
	{
		starttime = currtime;
		initialized = true;
	}
	return (((uint64_t)(currtime.tv_sec - starttime.tv_sec) * 1000000
			+ (currtime.tv_usec - starttime.tv_usec)) / 1000);
}
