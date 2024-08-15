/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:21:22 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_mallocs_to_null(t_philo *philo)
{
	philo->threads = NULL;
	philo->forks = NULL;
	philo->pdata = NULL;
	philo->common_data.meal_nb = NULL;
	philo->common_data.last_meal = NULL;
	philo->common_data.stop_simul_m = NULL;
	philo->stop_simul_m = NULL;
}

int	init_pdata(t_philo *philo)
{
	philo->pdata = (t_pdata *)ft_calloc(sizeof(t_pdata), philo->philo_nb);
	if (!philo->pdata)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

int	init_meal_nb(t_philo *philo)
{
	philo->common_data.meal_nb
		= (int *)ft_calloc(sizeof(int), philo->philo_nb);
	if (!philo->common_data.meal_nb)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

int	init_last_meal(t_philo *philo)
{
	philo->common_data.last_meal
		= (int *)ft_calloc(sizeof(int), philo->philo_nb);
	if (!philo->common_data.last_meal)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

int	init_values(t_philo *philo, char **argv, int argc)
{
	philo->ms_start = &philo->common_data.ms_start;
	philo->stop_simul = NOT_YET;
	philo->meal_nb_m = &philo->common_data.meal_nb_m;
	philo->last_meal_m = &philo->common_data.last_meal_m;
	philo->write_action_m = &philo->common_data.write_action_m;
	philo->philo_nb = ft_atoi(argv[1]);
	philo->common_data.ttd = ft_atoi(argv[2]);
	philo->common_data.tte = ft_atoi(argv[3]);
	philo->common_data.tts = ft_atoi(argv[4]);
	philo->ttd = &philo->common_data.ttd;
	philo->ms_start_m = &philo->common_data.ms_start_m;
	philo->common_data.create_status = 0;
	philo->common_data.meal_nb_targ = -1;
	if (argc == 6)
		philo->common_data.meal_nb_targ = ft_atoi(argv[5]);
	if (init_threads(philo) == FAIL
		|| init_meal_nb(philo) == FAIL
		|| init_last_meal(philo) == FAIL
		|| init_forks(philo) == FAIL
		|| init_stop_simul_m(philo) == FAIL)
		return (FAIL);
	init_mutexes(philo);
	if (init_pdata(philo) == FAIL)
		return (FAIL);
	return (fill_pdata(philo), SUCCESS);
}
