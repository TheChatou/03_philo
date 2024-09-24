/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_05_is_it_checkers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:04:04 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 19:07:46 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Retourne true si la simulation est terminée, tout en verifiant de maniere
// sécurisée grace a un mutex.
bool	is_finished_sim(t_data *data)
{
	if (get_bool_mtx(&data->data_mtx, &data->end_sim)
		|| get_bool_mtx(&data->data_mtx, &data->one_is_dead))
		return (true);
	return (false);
}

//	Retourne true si tout les threads sont prets, tout en verifiant de maniere
// sécurisée grace a un mutex.
bool	is_all_thr_ready(t_data *data)
{
	return (get_bool_mtx(&data->all_thr_ready_mtx, &data->all_threads_ready));
}

//	Retourne true si le philosophe a mange, tout en verifiant de maniere
// sécurisée grace a un mutex.
bool	is_philo_full(t_philo *philo)
{
	return (get_bool_mtx(&philo->philo_mtx, &philo->is_full));
}

//	Retourne true si un des philosophes est mort, tout en verifiant de maniere
// sécurisée grace a un mutex.
bool	is_philo_dead(t_philo *philo)
{
	return (get_bool_mtx(&philo->data->data_mtx, &philo->data->one_is_dead));
}

//	Retourne true si le philosophe est mort, tout en verifiant de maniere
// sécurisée grace a un mutex, en fonction de la derniere fois qu'il a mange, 
// et du temps de mort definie dans l'input.
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
