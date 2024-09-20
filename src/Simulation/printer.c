/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:56:51 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/20 16:18:15 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_debug(t_philo_action status, t_philo *philo, long elapsed)
{
	if (status == TAKE_A_FORK && !is_finished_sim(philo->data))
		printf("DEBUG : %-6ld : %d has taken the 'a' fork"
			"\t\t num [%d]\n", elapsed, philo->id, philo->a_fork->id);
	else if (status == TAKE_B_FORK && !is_finished_sim(philo->data))
		printf("DEBUG : %-6ld : %d has taken the 'b' fork"
			"\t\t num [%d]\n", elapsed, philo->id, philo->b_fork->id);
	else if (status == EAT && !is_finished_sim(philo->data))
		printf("DEBUG : "CYAN"%-6ld : %d is eating"
			"\t\t meal [%ld]\n", elapsed, philo->id, philo->nb_meal);
	else if (status == SLEEP && !is_finished_sim(philo->data))
		printf("DEBUG : "BLUE"%-6ld : %d is sleeping\n", elapsed, philo->id);
	else if (status == THINK && !is_finished_sim(philo->data))
		printf("DEBUG : "GREEN"%-6ld : %d is thinking\n", elapsed, philo->id);
	else if (status == DIE && !is_finished_sim(philo->data))
		printf("DEBUG : "RED"%-6ld : %d died\n", elapsed, philo->id);
}

void	print_status(t_philo_action status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->data->start_sim;
	if (is_philo_full(philo) || is_finished_sim(philo->data)
		|| is_philo_dead(philo))
		return ;
	safe_mutex(&philo->data->print_mtx, LOCK);
	if (debug)
		print_debug(status, philo, elapsed);
	if ((status == TAKE_A_FORK || status == TAKE_B_FORK)
		&& !is_finished_sim(philo->data))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EAT && !is_finished_sim(philo->data))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEP && !is_finished_sim(philo->data))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINK && !is_finished_sim(philo->data))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIE)
		printf("%ld %d died\n", elapsed, philo->id);
	safe_mutex(&philo->data->print_mtx, UNLOCK);
}

//	Colors ./print_status
// void	print_status(t_philo_action status, t_philo *philo, bool debug)
// {
// 	long	elapsed;

// 	elapsed = get_time(MILLISECOND) - philo->data->start_sim;
// 	if (philo->is_full || is_finished_sim(philo->data))
// 		return ;
// 	safe_mutex(&philo->data->print_mtx, LOCK);
// 	if (debug)
// 		print_debug(status, philo, elapsed);
// 	if ((status == TAKE_A_FORK || status == TAKE_B_FORK)
// 		&& !is_finished_sim(philo->data))
// 		printf(ITALIC "%ld\t" RESET BOLD "%d\t" RESET ITALIC" has taken a fork\n"
// 			RESET, elapsed, philo->id);
// 	else if (status == EAT && !is_finished_sim(philo->data))
// 		printf(ITALIC "%ld\t" RESET BOLD "%d\t" RESET ORANGE" is eating\n" RESET
// 			RESET, elapsed, philo->id);
// 	else if (status == SLEEP && !is_finished_sim(philo->data))
// 		printf(ITALIC "%ld\t" RESET BOLD "%d\t" RESET BLUE" is sleeping\n" RESET
// 			RESET, elapsed, philo->id);
// 	else if (status == THINK && !is_finished_sim(philo->data))
// 		printf(ITALIC "%ld\t" RESET BOLD "%d\t" RESET GREEN" is thinking\n" RESET
// 			RESET, elapsed, philo->id);
// 	else if (status == DIE)
// 	{
// 		printf(RED ITALIC "%ld\t" BOLD "%d\t died\n"RESET, elapsed, philo->id);
// 		set_bool_mtx(&philo->data->data_mtx, &philo->data->end_sim, true);
// 	}
// 	safe_mutex(&philo->data->print_mtx, UNLOCK);
// }