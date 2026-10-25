/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:41:53 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/16 18:53:03 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usage.h"

#include <stdio.h>

void	usage(char *filename)
{
	printf("Usage: %s <philo_cnt> <time_die> <time_eat> <time_sleep> "
			"[times_must_eat]\n"
		"Each argument represents\n"
		"- philo_cnt: total count of philosophers and forks\n"
		"- time_die: time (in ms) before philosopher dies from starving\n"
		"- time_eat: time (in ms) philosopher use for eating\n"
		"- time_sleep: time (in ms) philosopher use for sleep\n"
		"- times_must_eat: how much times each philosopher need to eat before "
		"simulation ends, unspecifies this means infinity\n",
		filename);
}
