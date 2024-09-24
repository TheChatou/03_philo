/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:07 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 19:03:24 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Focntion pour recuperer le temps actuel, en fonction du Time_code choisi :
// (SECOND, MILLISECOND, MICROSECOND).
long	get_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ft_putstr_fd2("Error while getting time", NULL), 0);
	if (time_code == SECOND)
		return (time.tv_sec + time.tv_usec / 1000000);
	else if (time_code == MILLISECOND)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (time_code == MICROSECOND)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		return (0);
}

//	Fonction pour attendre un certain temps en millisecondes.
void	precise_sleep(long msec, t_data *data)
{
	(void)data;
	if (msec < 0)
		msec = -msec;
	while (msec)
	{
		if (is_finished_sim(data))
			break ;
		if (msec > 1000)
		{
			usleep(1000 * 1000);
			msec -= 1000;
		}
		else
		{
			usleep(msec * 1000);
			break ;
		}
	}
}
