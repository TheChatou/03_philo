/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:30:49 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 19:01:52 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Lock Mutex pour les autres threads, avant de changer la valeur d'un booléen
void	set_bool_mtx(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

//	Lock Mutex pour les autres threads, retourne la valeur du booléen argument.
bool	get_bool_mtx(t_mtx *mutex, bool *src)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *src;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

//	Lock Mutex pour les autres threads, avant de changer la valeur d'un long
void	set_long_mtx(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

//	Lock Mutex pour les autres threads, retourne la valeur du long argument.
long	get_long_mtx(t_mtx *mutex, long *src)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *src;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}
