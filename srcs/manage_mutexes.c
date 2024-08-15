/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:27:54 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_philo *philo)
{
	philo->forks
		= (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t),
			philo->philo_nb);
	if (!philo->forks)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

int	init_stop_simul_m(t_philo *philo)
{
	philo->common_data.stop_simul_m
		= (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t),
			philo->philo_nb);
	if (!philo->common_data.stop_simul_m)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

void	init_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_nb)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		pthread_mutex_init(&philo->common_data.stop_simul_m[i], NULL);
	}
	i = -1;
	while (++i < philo->philo_nb)
	{
		philo->stop_simul_m = &philo->common_data.stop_simul_m[i];
		philo->stop_simul_m++;
	}
	i = -1;
	while (++i < philo->philo_nb)
		philo->stop_simul_m--;
	pthread_mutex_init(philo->ms_start_m, NULL);
	pthread_mutex_init(philo->last_meal_m, NULL);
	pthread_mutex_init(philo->meal_nb_m, NULL);
	pthread_mutex_init(philo->write_action_m, NULL);
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->forks && *(int *)philo->forks != 0)
		while (++i < philo->philo_nb)
			pthread_mutex_destroy(&philo->forks[i]);
	i = -1;
	if (philo->common_data.stop_simul_m && *(int *)philo->stop_simul_m != 0)
		while (++i < philo->philo_nb)
			pthread_mutex_destroy(&philo->common_data.stop_simul_m[i]);
	if (*(int *)philo->ms_start_m != 0)
		pthread_mutex_destroy(philo->ms_start_m);
	if (*(int *)philo->last_meal_m != 0)
		pthread_mutex_destroy(philo->last_meal_m);
	if (*(int *)philo->meal_nb_m != 0)
		pthread_mutex_destroy(philo->meal_nb_m);
	if (*(int *)philo->write_action_m != 0)
		pthread_mutex_destroy(philo->write_action_m);
}
