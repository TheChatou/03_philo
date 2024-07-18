/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:48:32 by chatou            #+#    #+#             */
/*   Updated: 2024/07/17 12:26:31 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_malloc(size_t bytes)
{
	void	*ptr;
	
	ptr = malloc(bytes);
	if (NULL == ptr)
		error_exit("Malloc failed");
	return (ptr);
}

static void	handle_mutex_error(int status, t_actions acode)
{
	if (status != 0)
	{
		if (status == EINVAL && (acode == LOCK || acode == UNLOCK))
			error_exit("The value is specified by mutex is invalid.");
		else if (status == EINVAL && acode == INIT)
			error_exit("The value specified by attr is invalid.");
		else if (status == EDEADLK)
			error_exit("A deadlock condition was detected.");
		else if (status == EPERM)
			error_exit("The current thread does not hold a lock on mutex.");
		else if (status == ENOMEM)
			error_exit("Insufficient memory exists to initialize the mutex.");
		else if (status == EBUSY)
			error_exit("Mutex is already locked.");	
	}
}

void	safe_mutex_init(t_mtx *mutex, t_actions acode)
{
	if (acode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), acode);
	else if (acode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), acode);
	else if (acode == INIT)
		handle_mutex_errorp(thread_mutex_init(mutex, NULL), acode);
	else if (acode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), acode);
	else
		error_exit("Invalid action code");
}

static void	handle_thread_error(int status, t_actions acode)
{
	if (status != 0)
	{
		if (status == EINVAL && (acode == JOIN || acode == DETACH))
			error_exit("The value is specified by attr is invalid.");
		else if (status == EINVAL && acode == CREATE)
			error_exit("The value specified by thread is not joinable.");
		else if (status == EDEADLK)
			error_exit("A deadlock condition was detected or the value of thread specifies the calling thread.");
		else if (status == EPERM)
			error_exit("The caller does not have appropriate permission.");
		else if (status == EAGAIN)
			error_exit("No resources to create a new thread.");
		else if (status == ESRCH)
			error_exit("No thread could be found corresponding to that specified by the given thread ID.");	
	}
}

void	safe_thread_create(pthread_t *thread, void *(*start)(void *), void *data, t_actions acode)
{
	if (acode == CREATE)
		handle_mutex_error(pthread_create(thread, NULL, start, data), acode);
	else if (acode == JOIN)
		handle_mutex_error(pthread_join(*thread, NULL), acode);
	else if (acode == DETACH)
		handle_mutex_error(pthread_detach(*thread), acode);
	else
		error_exit("Invalid action code");
}
