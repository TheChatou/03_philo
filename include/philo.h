/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:26:24 by chatou            #+#    #+#             */
/*   Updated: 2024/09/20 15:35:54 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

////////////////////////////////////////////////////////////////////////////////
//	LIBS	 ///////////////////////////////////////////////////////////////////
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include "colors.h"

////////////////////////////////////////////////////////////////////////////////
//	MACROS	 ///////////////////////////////////////////////////////////////////
# define BLACK          "\001\033[0;30m\002"
# define RED            "\001\033[0;31m\002"
# define GREEN          "\001\033[0;32m\002"
# define YELLOW         "\001\033[0;33m\002"
# define BLUE           "\001\033[0;34m\002"
# define MAGENTA        "\001\033[0;35m\002"
# define CYAN           "\001\033[0;36m\002"
# define WHITE          "\001\033[0;37m\002"
# define ORANGE         "\001\033[38;5;208m\002"
# define RESET          "\001\033[0m\002"

# define NO_DEBUG		0
# define DEBUG			1

//- ENUM	-------------------------------------------------------------------/
typedef enum e_action_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}					t_action_code;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}					t_time_code;

typedef enum e_philo_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_A_FORK,
	TAKE_B_FORK,
	DIE,
}					t_philo_action;

////////////////////////////////////////////////////////////////////////////////
//	STRUCTS		////////////////////////////////////////////////////////////////
typedef pthread_mutex_t	t_mtx;

// - Fork_mtx : Mutex pour proteger les fourchettes
typedef struct s_fork
{
	int				id;
	t_mtx			fork_mtx;
}					t_fork;

//	- Philo_mtx : Mutex pour proteger les donnees du philosophe
typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			nb_meal;
	bool			is_full;
	bool			is_joined;
	pthread_t		thread_id;
	t_fork			*a_fork;
	t_fork			*b_fork;
	t_mtx			philo_mtx;
	struct s_data	*data;
}					t_philo;

//	- All_threads_ready : Bool pour savoir si tous les threads sont prets
//  - Data_mtx : Mutex pour synchroniser les donnees, afin d'eviter que
// les threads n'accedent en meme temps aux donnees partagees
// (philos, forks, etc) 
//  - Print_mtx : Mutex pour synchroniser l'affichage, afin d'eviter que
// les philosophes n'affichent en meme temps leurs actions
typedef struct s_data
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			rounds;
	long			start_sim;
	bool			start_threads;
	bool			*nb_philos_full;
	bool			end_sim;
	bool			one_is_dead;
	bool			all_threads_ready;
	t_philo			*philos;
	t_fork			*forks;
	t_mtx			data_mtx;
	t_mtx			print_mtx;
	t_mtx			all_thr_ready_mtx;
}					t_data;

////////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS	////////////////////////////////////////////////////////////////
//------------------------------	Init_And_Set	--------------------------//
//- Init_And_Set_00.c	-------------------------------------------------------/
void			init_fork(t_fork *fork);
void			init_philo(t_philo *philo);
void			init_data(t_data *data);
bool			init_n_malloc_full_bools(t_data *data, int max_philos);
bool			init_malloc_n_set_forks(t_data *data, long max_philos);

//- Init_And_Set_01.c	-------------------------------------------------------/
bool			set_data(t_data *data, char **av);
bool			set_data_args(t_data *data, char **av);
bool			init_malloc_n_set_philos(t_data *data, long max_philos);
bool			set_philos(t_data *data, t_philo *philo, int i);
void			assign_forks(t_philo *philo, t_fork *forks, int pos);

//------------------------------	Simulation	------------------------------//
//- checker.c	---------------------------------------------------------------/
void			sim_checker(t_data *data);
bool			is_all_philos_full(t_philo *philos, int max_philos);

//- dinner.c	---------------------------------------------------------------/
bool			start_sim(t_data *data);
void			*dinner_sim(void *data);
void			philo_eat(t_philo *philo);
void			philo_sleep_n_think(t_philo *philo);
void			one_sad_dead_philosopher(t_data *data);

//- printer.c	---------------------------------------------------------------/
void			print_status(t_philo_action status, t_philo *philo, bool debug);
void			print_debug(t_philo_action status, t_philo *philo,
					long elapsed);

//------------------------------	Utils	----------------------------------//
//- utils_00_mtx_n_thr.c	---------------------------------------------------/
bool			mutex_error(int status, t_action_code acode);
bool			safe_mutex(t_mtx *mutex, t_action_code acode);
bool			thread_error(int status, t_action_code acode);
bool			safe_thread(pthread_t *thread, void *(*start)(void *),
					void *data, t_action_code acode);

//- utils_01_mutex.c	-------------------------------------------------------/
long			get_long_mtx(t_mtx *mutex, long *src);
void			set_long_mtx(t_mtx *mutex, long *dest, long value);
bool			get_bool_mtx(t_mtx *mutex, bool *src);
void			set_bool_mtx(t_mtx *mutex, bool *dest, bool value);

//- utils_02_classics.c	-------------------------------------------------------/
bool			is_digit(char c);
bool			is_space(char c);
const char		*valid_input(const char *str);
long			ft_atol(const char *str);
void			ft_putstr_fd2(char *str, char *arg);

//- utils_03_free.c		-------------------------------------------------------/
void			free_mtxs(t_data *data);
void			join_threads(t_data *data);
bool			free_sim(t_data *data);

//- utils_04_time.c		-------------------------------------------------------/
long			get_time(t_time_code time_code);
void			precise_sleep(long usec, t_data *data);

//- utils_05_is_it_checker.c	-----------------------------------------------/
bool			is_finished_sim(t_data *data);
bool			is_all_thr_ready(t_data *data);
bool			is_philo_full(t_philo *philo);
bool			is_philo_dead(t_philo *philo);
bool			is_starving(t_philo *philo);

#endif