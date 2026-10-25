/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guarded_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:26:46 by pkongkha          #+#    #+#             */
/*   Updated: 2026/10/25 22:58:30 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUARDED_TYPE_H
# define GUARDED_TYPE_H

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>

struct s_guarded_timeval
{
	pthread_mutex_t	lock;
	struct timeval	tv;
};

void			guarded_timeval_write(struct s_guarded_timeval *var,
			struct timeval value);
struct timeval	guarded_timeval_read(struct s_guarded_timeval *var);
void	guarded_timeval_update_curr(struct s_guarded_timeval *guarded_tv);

struct s_guarded_bool
{
	pthread_mutex_t	lock;
	bool			value;
};

void	guarded_bool_write(struct s_guarded_bool *var, bool value);
bool	guarded_bool_read(struct s_guarded_bool *var);

struct s_guarded_ssize_t
{
	pthread_mutex_t	lock;
	ssize_t			value;
};

void	guarded_ssize_t_write(struct s_guarded_ssize_t *var, ssize_t value);
ssize_t	guarded_ssize_t_read(struct s_guarded_ssize_t *var);
#endif
