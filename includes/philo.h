/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:59:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:41:27 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// includes

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

// return and exit status

# define SUCCESS 0
# define FAIL 1
# define STOP 2

// did someone died ?

# define YES 1
# define NOT_YET 0

// error messages

# define E_INV_PARAM "Invalid argument number."
# define E_NO_DIGITS "Only use digit and positive arguments."
# define E_NEG_OR_NULL_PHILO "One or more philo should be sit at the table."
# define E_NEG_OR_NULL_TS "All time arguments should be higher than 0."
# define E_NEG_MEALS "The number of meals should be equal or higher than 0."
# define E_SHORT_INT_MAX "No arg should exceed the value of SHRT_MAX (32767)."

# define E_NULL_MALLOC "Null value due to a failed malloc."
# define E_FAILED_MALLOC "Failed malloc."
# define E_PTHREAD_JOIN "The function pthread_join failed."
# define E_GET_TOTD "The function gettimeofday failed."
# define E_PTHREAD_CREATE "The function pthread_create failed."
# define E_MUT_L "The function pthread_mutex_lock failed."
# define E_MUT_U "The function pthread_mutex_unlock failed."

typedef struct s_common_data
{
	int				ts_0;
	pthread_mutex_t	ms_start_m;
	int				tte;
	int				tts;
	int				ttd;
	int				meal_nb_targ;
	int				ms_start;
	int				create_status;
	int				*meal_nb;
	pthread_mutex_t	meal_nb_m;
	int				*last_meal;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	write_action_m;
	pthread_mutex_t	*stop_simul_m;
}	t_common_data;

typedef struct s_pdata
{
	int				ts_0;
	int				second_ts;
	pthread_mutex_t	*ms_start_m;
	int				id;
	int				*philo_nb;
	pthread_mutex_t	*left_fork_m;
	pthread_mutex_t	*right_fork_m;
	int				*ms_start;
	int				*meal_nb;
	pthread_mutex_t	*meal_nb_m;
	int				*last_meal;
	pthread_mutex_t	*last_meal_m;
	int				*ttd;
	int				*tte;
	int				*tts;
	int				stop_simul;
	pthread_mutex_t	*stop_simul_m;
	pthread_mutex_t	*write_action_m;
	int				locked_right_fork;
	int				locked_left_fork;
	t_common_data	common_data;
}	t_pdata;

typedef struct s_philo
{
	int				ts_0;
	int				*ms_start;
	pthread_mutex_t	*ms_start_m;
	int				philo_nb;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stop_simul_m;
	t_pdata			*pdata;
	t_common_data	common_data;
	int				*ttd;
	int				stop_simul;
	pthread_mutex_t	*last_meal_m;
	pthread_mutex_t	*meal_nb_m;
	pthread_mutex_t	*write_action_m;
}	t_philo;

// arg_checking

int					are_args_valid(char **argv, int argc);

// init_values

int					init_values(t_philo *philo, char **argv, int argc);
int					init_threads(t_philo *philo);
int					init_forks(t_philo *philo);
int					init_stop_simul_m(t_philo *philo);
void				set_mallocs_to_null(t_philo *philo);
void				init_stop_simul_m_philo(t_philo *philo);

// init_pdata

void				fill_pdata(t_philo *philo);

// manage_threads

int					create_pthreads(t_philo *philo);
int					join_threads(t_philo *philo);

// quit_program

int					print_mess(t_pdata *pdata, int i, char *mess, int status);
void				clean_all(t_philo *philo);
void				quit_program(t_philo *philo, int i, char *mess, int status);

// utility_functions

int					ft_atoi(const char *str);
long int			ft_atol(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				ft_putstr_fd(char *s, int fd);

// actions

int					homemade_usleep(t_pdata *pdata, int time_in_ms);
void				*philo_routine(void *content);
int					has_taken_a_fork_left(t_pdata *pdata);
int					has_taken_a_fork_right(t_pdata *pdata);
int					is_eating(t_pdata *pdata);
int					unlock_forks(t_pdata *pdata);
int					is_sleeping(t_pdata *pdata);
int					is_thinking(t_pdata *pdata);
int					write_act(t_pdata *pdata, int id, char *act, int ts_0);

// manage mutexes

void				init_mutexes(t_philo *philo);
void				destroy_mutexes(t_philo *philo);

// big_brother

void				*big_brother(void *content);

// fork management

int					has_taken_a_fork_left(t_pdata *pdata);
int					has_taken_a_fork_right(t_pdata *pdata);
int					unlock_forks(t_pdata *pdata);
int					take_forks_depending_on_id(t_pdata *pdata);

// routine utilities

int					homemade_usleep(t_pdata *pdata, int time_in_ms);
int					write_act(t_pdata *pdata, int id, char *act, int ts_0);
int					get_starting_ts(t_philo *philo);
int					get_current_ts(t_pdata *pdata);

#endif
