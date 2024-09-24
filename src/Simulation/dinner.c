/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:20:08 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 18:55:18 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Lance la simulation, si il n'y a qu'un philosophe, il meurt tristement.
// Puis creer les threads pour chaque philosophe et grace au mutex
// all_thr_ready_mtx, attend que tous les threads soient prets avant de lancer
// la simulation. Enfin, lance la simulation et le moniteur.
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

//	Routine des threads des philosophes. Le lock sur all_thr_ready_mtx, attend
// la boucle de creation des threads de la fonction mere UNLOCK avant de pouvoir
// le LOCK ici. Puis, si le philosophe est impair, il attend time_to_eat avant
// de commencer la simulation. Ensuite le premier philosophe pair attend aussi.
// Enfin, tant que le philosophe n'est pas mort, que la simulation n'est pas
// finie et que le philosophe n'a pas mange le nombre de fois demande, il mange
// puis dort et pense.
void	*dinner_sim(void *d_philo)
{
	t_philo	*philo;

	philo = (t_philo *)d_philo;
	safe_mutex(&philo->data->all_thr_ready_mtx, LOCK);
	safe_mutex(&philo->data->all_thr_ready_mtx, UNLOCK);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	if (philo->id % 2 == 1)
		precise_sleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nb_philo % 2 == 1 && philo->id % 2 == 2)
		precise_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!is_philo_dead(philo) && !is_finished_sim(philo->data)
		&& !is_philo_full(philo))
	{
		philo_eat(philo);
		philo_sleep_n_think(philo);
	}
	return (NULL);
}

//	Le philosophe prend les fourchettes, mange, puis les relache.
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

//	Le philosophe dort et pense.
// Si le nombre de philosophe est impair et si le temps de manger est
// superieur ou egal au temps de dormir, il dort 2 fois le temps de manger
// moins le temps de dormir. Sinon il ne dort pas.
void	philo_sleep_n_think(t_philo *philo)
{
	long	time_to_wait;

	if (philo->data->time_to_eat >= philo->data->time_to_sleep)
		time_to_wait = 2 * philo->data->time_to_eat
			- philo->data->time_to_sleep;
	else
		time_to_wait = 0;
	print_status(SLEEP, philo, NO_DEBUG);
	precise_sleep(philo->data->time_to_sleep, philo->data);
	print_status(THINK, philo, NO_DEBUG);
	if (philo->data->nb_philo % 2 == 1)
		precise_sleep(time_to_wait, philo->data);
}

//	Si il n'y a qu'un philosophe, il meurt tristement, apres avoir attendu
// le temps de mourir.
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
