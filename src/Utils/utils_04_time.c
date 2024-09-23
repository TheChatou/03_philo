/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeada-si <jeada-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:07 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 14:01:50 by jeada-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	precise_sleep(long msec, t_data *data)
{
	long	start;
	long	delta;
	long	remaining;

	(void)data;
	start = get_time(MILLISECOND);
	while (get_time(MILLISECOND) - start < msec)
	{
		if (is_finished_sim(data))
			break ;
		delta = get_time(MILLISECOND) - start;
		remaining = msec - delta;
		if (remaining > 1000)
			usleep(msec / 2);
		else
			while (get_time(MILLISECOND) - start < msec)
				;
	}
}
