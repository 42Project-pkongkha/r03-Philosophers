/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:26:46 by pkongkha          #+#    #+#             */
/*   Updated: 2026/11/01 21:27:47 by pkongkha         ###   ########.fr       */
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

struct s_guarded_int
{
	pthread_mutex_t	lock;
	int				value;
};

void		guarded_int_write(struct s_guarded_int *g_int, int value);
int			guarded_int_read(struct s_guarded_int *g_int);

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
