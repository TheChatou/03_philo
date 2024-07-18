/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:26:24 by chatou            #+#    #+#             */
/*   Updated: 2024/07/17 12:18:15 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

////////////////////////////////////////////////////////////////////////////////
//	LIBS	 ///////////////////////////////////////////////////////////////////
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

////////////////////////////////////////////////////////////////////////////////
//	MACROS	 ///////////////////////////////////////////////////////////////////
typedef enum e_actions
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}            t_actions;


////////////////////////////////////////////////////////////////////////////////
//	STRUCTS		////////////////////////////////////////////////////////////////
typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	bool			is_eating;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mtx			*print;
	struct s_data	*data;
}            t_philo;

typedef struct s_fork
{
	int				id;
	t_mtx			mutex;
}            t_fork;

typedef struct s_data
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	long			start_time;
	bool			dead;
	t_philo			*philo;
	t_fork			*fork;
	t_mtx			print;
}            t_data;

////////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS 	////////////////////////////////////////////////////////////////

#endif