/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:20:08 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 15:09:15 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Lance la simulation, la premiere boucle cree les threads,
// et execute les actions des philosophes (eat, sleep, think).
// Prend le temps de debut de la simulation, puis la seconde boucle
// attend que tous les threads aient fini.
void	start_sim(t_data *data)
{
	int		i;

	i = -1;
	if (data->nb_philo == 1)
		return (one_sad_dead_philosopher(data));
	data->start_threads = true;
	safe_mutex(&data->all_thr_ready_mtx, LOCK);
	while (++i < data->nb_philo)
		if (!safe_thread(&data->philos[i].thread_id, dinner_sim,
				&data->philos[i], CREATE))
			return ;
	safe_mutex(&data->all_thr_ready_mtx, UNLOCK);
	data->start_sim = get_time(MILLISECOND);
	if (!data->start_sim)
		return ;
	return (monitor_sim(data));
}

//	Fonction principale des threads, qui execute les actions des philosophes
// (eat, sleep, think) tant que la simulation n'est pas finie.
void	*dinner_sim(void *d_philo)
{
	t_philo	*philo;

	philo = (t_philo *)d_philo;
	safe_mutex(&philo->data->all_thr_ready_mtx, LOCK);
	precise_sleep(1, philo->data);
	safe_mutex(&philo->data->all_thr_ready_mtx, UNLOCK);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	if (philo->id % 2 == 1)
		precise_sleep(philo->data->time_to_eat, philo->data);
	if (philo->id == 1 && philo->data->nb_philo % 2 == 1)
		precise_sleep(philo->data->time_to_eat, philo->data);
	while (!is_philo_dead(philo) && !is_finished_sim(philo->data)
		&& !is_philo_full(philo))
	{
		philo_eat(philo);
		philo_sleep_n_think(philo);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	safe_mutex(&philo->a_fork->fork_mtx, LOCK);
	print_status(TAKE_A_FORK, philo, NO_DEBUG);
	safe_mutex(&philo->b_fork->fork_mtx, LOCK);
	print_status(TAKE_B_FORK, philo, NO_DEBUG);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	philo->nb_meal++;
	print_status(EAT, philo, NO_DEBUG);
	precise_sleep(philo->data->time_to_eat, philo->data);
	if (philo->data->rounds > 0 && philo->data->rounds == philo->nb_meal)
		set_bool_mtx(&philo->philo_mtx, &philo->is_full, true);
	safe_mutex(&philo->a_fork->fork_mtx, UNLOCK);
	safe_mutex(&philo->b_fork->fork_mtx, UNLOCK);
}

void	philo_sleep_n_think(t_philo *philo)
{
	print_status(SLEEP, philo, NO_DEBUG);
	precise_sleep(philo->data->time_to_sleep, philo->data);
	print_status(THINK, philo, NO_DEBUG);
	if (philo->data->nb_philo % 2 == 1 && philo->id % 2 == 1)
		precise_sleep(philo->data->time_to_eat * 2
			- philo->data->time_to_sleep, philo->data);
	else
		precise_sleep(philo->data->time_to_eat
			- philo->data->time_to_die, philo->data);
}

void	one_sad_dead_philosopher(t_data *data)
{
	data->start_sim = get_time(MILLISECOND);
	if (!data->start_sim)
	{
		ft_putstr_fd2("Error: get_time failed\n", NULL);
		return ;
	}
	precise_sleep(data->time_to_die, data);
	print_status(DIE, &data->philos[0], NO_DEBUG);
}
