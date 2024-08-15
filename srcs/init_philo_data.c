/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:22:32 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*get_left_fork_id(t_philo *philo, int id)
{
	if (id == 1)
		return (&philo->forks[philo->philo_nb - 1]);
	else
		return (&philo->forks[id - 2]);
}

pthread_mutex_t	*get_right_fork_id(t_philo *philo, int id)
{
	return (&philo->forks[id - 1]);
}

void	fill_mutex_data(t_philo *philo, int i)
{
	philo->pdata[i].stop_simul_m = &philo->stop_simul_m[i];
	philo->pdata[i].ms_start_m = &philo->common_data.ms_start_m;
	philo->pdata[i].meal_nb_m = &philo->common_data.meal_nb_m;
	philo->pdata[i].write_action_m = &philo->common_data.write_action_m;
	philo->pdata[i].right_fork_m = get_right_fork_id(philo, i + 1);
	philo->pdata[i].left_fork_m = get_left_fork_id(philo, i + 1);
}

void	fill_pdata(t_philo *philo)
{
	int				i;
	int				current_ts_in_ms;

	current_ts_in_ms = get_current_ts(philo->pdata);
	i = -1;
	while (++i < philo->philo_nb)
	{
		philo->pdata[i].ts_0 = current_ts_in_ms;
		philo->pdata[i].id = i + 1;
		philo->pdata[i].locked_right_fork = 1;
		philo->pdata[i].locked_left_fork = 1;
		philo->pdata[i].philo_nb = &philo->philo_nb;
		philo->pdata[i].stop_simul = NOT_YET;
		philo->pdata[i].meal_nb = &philo->common_data.meal_nb[i];
		philo->pdata[i].last_meal = &philo->common_data.last_meal[i];
		philo->pdata[i].last_meal_m = &philo->common_data.last_meal_m;
		philo->pdata[i].ms_start = &philo->common_data.ms_start;
		philo->pdata[i].ttd = &philo->common_data.ttd;
		philo->pdata[i].tte = &philo->common_data.tte;
		philo->pdata[i].tts = &philo->common_data.tts;
		fill_mutex_data(philo, i);
	}
	philo->ts_0 = current_ts_in_ms;
}
