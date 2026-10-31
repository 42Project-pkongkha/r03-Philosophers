/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:26:46 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/31 19:10:40 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUARDED_TYPE_H
# define GUARDED_TYPE_H

# include "philo_types.h"

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>

struct s_guarded_bool
{
	pthread_mutex_t	lock;
	bool			value;
};

void		guarded_bool_write(struct s_guarded_bool *g_bool, bool value);
bool		guarded_bool_read(struct s_guarded_bool *g_bool);

struct s_guarded_ssize
{
	pthread_mutex_t	lock;
	ssize_t			value;
};

void		guarded_ssize_write(struct s_guarded_ssize *g_ssize, ssize_t value);
ssize_t		guarded_ssize_read(struct s_guarded_ssize *g_ssize);

struct s_guarded_mseconds
{
	pthread_mutex_t	lock;
	t_mseconds		msec;
};

void		guarded_mseconds_write(
				struct s_guarded_mseconds *g_msec,
				t_mseconds msec
				);
t_mseconds	guarded_mseconds_read(struct s_guarded_mseconds *g_msec);
#endif
