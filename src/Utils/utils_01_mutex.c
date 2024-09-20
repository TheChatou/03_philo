/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:30:49 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/18 18:04:02 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Lock Mutex for other threads, before changing the value of a bool
// then unlock it.
void	set_bool_mtx(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

//	Lock Mutex for other threads, return the value of the bool argument.
bool	get_bool_mtx(t_mtx *mutex, bool *src)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *src;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

//	Lock Mutex for other threads, before changing the value of a long
void	set_long_mtx(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

//	Lock Mutex for other threads, return the value of the long argument.
long	get_long_mtx(t_mtx *mutex, long *src)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *src;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}
