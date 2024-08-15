/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commute_job_sleep_actions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:21 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 22:44:06 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating_stuff(t_pdata *pdata)
{
	if (write_act(pdata, pdata->id, "is eating", pdata->ts_0) == FAIL)
		return (FAIL);
	if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	if (pthread_mutex_lock(pdata->last_meal_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	*(int *)pdata->last_meal = get_current_ts(pdata) - pdata->ts_0;
	if (pthread_mutex_unlock(pdata->last_meal_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	if (*(int *)pdata->last_meal == -1)
		return (FAIL);
	if (pthread_mutex_lock(pdata->meal_nb_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	*(int *)pdata->meal_nb += 1;
	if (pthread_mutex_unlock(pdata->meal_nb_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	homemade_usleep(pdata, *(int *)pdata->tte);
	return (SUCCESS);
}

int	is_eating(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (is_eating_stuff(pdata) == FAIL)
			return (FAIL);
	}
	else
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

int	is_sleeping(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (write_act(pdata, pdata->id, "is sleeping", pdata->ts_0) == FAIL)
			return (FAIL);
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		homemade_usleep(pdata, *(int *)pdata->tts);
	}
	else
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

int	is_thinking(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (write_act(pdata, pdata->id, "is thinking", pdata->ts_0) == FAIL)
			return (FAIL);
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	}
	else
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}
