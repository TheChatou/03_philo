/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_05_is_it_checkers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:04:04 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/20 16:17:55 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_finished_sim(t_data *data)
{
	if (get_bool_mtx(&data->data_mtx, &data->end_sim)
		|| get_bool_mtx(&data->data_mtx, &data->one_is_dead))
		return (true);
	return (false);
}

bool	is_all_thr_ready(t_data *data)
{
	return (get_bool_mtx(&data->all_thr_ready_mtx, &data->all_threads_ready));
}

bool	is_philo_full(t_philo *philo)
{
	return (get_bool_mtx(&philo->philo_mtx, &philo->is_full));
}

bool	is_philo_dead(t_philo *philo)
{
	return (get_bool_mtx(&philo->philo_mtx, &philo->data->one_is_dead));
}

bool	is_starving(t_philo *philo)
{
	bool	result;

	result = false;
	safe_mutex(&philo->philo_mtx, LOCK);
	if (philo->last_meal && !philo->is_full)
		result = (get_time(MILLISECOND) - philo->last_meal
				>= philo->data->time_to_die);
	safe_mutex(&philo->philo_mtx, UNLOCK);
	return (result);
}
