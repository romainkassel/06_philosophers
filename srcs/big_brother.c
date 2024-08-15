/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:21 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 21:27:42 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	three_two_one_gooooo_big_brother(t_philo *philo)
{
	while (1)
	{
		usleep(1);
		if (get_current_ts(philo->pdata)
			>= (philo->ts_0 + 100))
		{
			philo->ts_0 = get_current_ts(philo->pdata);
			return (SUCCESS);
		}
	}
	return (FAIL);
}

int	set_stop_simul_to_yes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_nb)
	{
		if (pthread_mutex_lock(philo->stop_simul_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_L, FAIL), FAIL);
		philo->pdata[i].stop_simul = YES;
		if (pthread_mutex_unlock(philo->stop_simul_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
		philo->stop_simul_m++;
	}
	i = -1;
	while (++i < philo->philo_nb)
		philo->stop_simul_m--;
	philo->stop_simul = YES;
	return (SUCCESS);
}

int	supervise_meal_nb(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nb)
	{
		if (pthread_mutex_lock(philo->meal_nb_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_L, FAIL), FAIL);
		if (*(int *)philo->pdata[i].meal_nb < philo->common_data.meal_nb_targ)
		{
			if (pthread_mutex_unlock(philo->meal_nb_m) != 0)
				return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
			return (SUCCESS);
		}
		if (pthread_mutex_unlock(philo->meal_nb_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
		i++;
	}
	set_stop_simul_to_yes(philo);
	return (STOP);
}

int	supervise_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_nb)
	{
		if (pthread_mutex_lock(philo->last_meal_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_L, FAIL), FAIL);
		if (((get_current_ts(philo->pdata) - philo->ts_0)
				- *(int *)philo->pdata[i].last_meal) >= *(int *)philo->ttd)
		{
			if (pthread_mutex_unlock(philo->last_meal_m) != 0)
				return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
			set_stop_simul_to_yes(philo);
			if (write_act(philo->pdata, i + 1, "died", philo->ts_0) == FAIL)
				return (FAIL);
			return (STOP);
		}
		if (pthread_mutex_unlock(philo->last_meal_m) != 0)
			return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
	}
	return (SUCCESS);
}

void	*big_brother(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (three_two_one_gooooo_big_brother(philo) == FAIL)
		return ((void *)FAIL);
	while (1)
	{
		usleep(1);
		if (philo->stop_simul == YES)
			return ((void *)STOP);
		if (philo->common_data.meal_nb_targ != -1)
			supervise_meal_nb(philo);
		supervise_death(philo);
	}
	return ((void *)SUCCESS);
}
