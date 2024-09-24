/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00_mtx_n_thr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:48:32 by chatou            #+#    #+#             */
/*   Updated: 2024/09/23 19:01:16 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//	Fonction pour Lock, Unlock, Init et Destroy un mutex, et check les erreurs.
// Elle retourne false si une erreur est detectée, avec un message d'erreur.
bool	safe_mutex(t_mtx *mutex, t_action_code acode)
{
	if (acode == LOCK)
		return (mutex_error(pthread_mutex_lock(mutex), acode));
	else if (acode == UNLOCK)
		return (mutex_error(pthread_mutex_unlock(mutex), acode));
	else if (acode == INIT)
		return (mutex_error(pthread_mutex_init(mutex, NULL), acode));
	else if (acode == DESTROY)
		return (mutex_error(pthread_mutex_destroy(mutex), acode));
	else
		return (ft_putstr_fd2("Invalid action code", NULL), false);
}

//	Fonction pour Create, Join, Detach un thread, et check les erreurs.
// Elle retourne false si une erreur est detectée, avec un message d'erreur.
bool	safe_thread(pthread_t *thread, void *(*start)(void *),
		void *data, t_action_code acode)
{
	if (acode == CREATE)
		return (thread_error(pthread_create(thread, NULL, start, data), acode));
	else if (acode == JOIN)
		return (thread_error(pthread_join(*thread, NULL), acode));
	else if (acode == DETACH)
		return (thread_error(pthread_detach(*thread), acode));
	else
		return (ft_putstr_fd2("Invalid action code", NULL), false);
}

//	Fontcion qui gere les messages d'erreurs des mutex.
bool	mutex_error(int status, t_action_code acode)
{
	if (status != 0)
	{
		if (status == EINVAL && (acode == LOCK || acode == UNLOCK))
			return (ft_putstr_fd2("The value is specified by mutex is invalid.",
					NULL), false);
		else if (status == EINVAL && acode == INIT)
			return (ft_putstr_fd2("The value specified by attr is invalid.",
					NULL), false);
		else if (status == EDEADLK)
			return (ft_putstr_fd2("A deadlock condition was detected.",
					NULL), false);
		else if (status == EPERM)
			return (ft_putstr_fd2("The current thread does not hold a lock"
					" on mutex.", NULL), false);
		else if (status == ENOMEM)
			return (ft_putstr_fd2("Insufficient memory exists to initialize "
					"the mutex.", NULL), false);
		else if (status == EBUSY)
			return (ft_putstr_fd2("Mutex is already locked.", NULL), false);
	}
	return (true);
}

//	Fonction qui gere les messages d'erreurs des threads.
bool	thread_error(int status, t_action_code acode)
{
	if (status != 0)
	{
		if (status == EINVAL && (acode == JOIN || acode == DETACH))
			return (ft_putstr_fd2("The value is specified by attr is invalid.",
					NULL), false);
		else if (status == EINVAL && acode == CREATE)
			return (ft_putstr_fd2("The value of the thread is not joinable.",
					NULL), false);
		else if (status == EDEADLK)
			return (ft_putstr_fd2("A deadlock condition was detected or the "
					"value of thread specifies the calling thr.", NULL), false);
		else if (status == EPERM)
			return (ft_putstr_fd2("The caller does not have appropriate."
					"permission", NULL), false);
		else if (status == EAGAIN)
			return (ft_putstr_fd2("No resources to create a new thread.",
					NULL), false);
		else if (status == ESRCH)
			return (ft_putstr_fd2("No thread could be found corresponding to "
					"that specified by the given thread ID.", NULL), false);
	}
	return (true);
}
