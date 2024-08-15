/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commute_job_sleep_routine.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:21 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 21:27:18 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*routine_preparation(t_pdata *pdata)
{
	if (*(int *)pdata->philo_nb == 1)
	{
		if (pthread_mutex_lock(pdata->right_fork_m) != 0)
			return (print_mess(pdata, 1, E_MUT_L, FAIL), (int *)FAIL);
		if (write_act(pdata, pdata->id,
				"has taken a fork", pdata->ts_0) == FAIL)
			return ((int *)FAIL);
		homemade_usleep(pdata, *(int *)pdata->ttd);
		if (pthread_mutex_unlock(pdata->right_fork_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), (int *)FAIL);
		return ((int *)STOP);
	}
	if (pdata->id % 2 == 1)
		homemade_usleep(pdata, 10);
	if (*(int *)pdata->philo_nb % 2 == 1 && pdata->id == 1)
		homemade_usleep(pdata, *(int *)pdata->tte);
	return ((int *)SUCCESS);
}

int	philo_sub_routines(t_pdata *pdata)
{
	if (take_forks_depending_on_id(pdata) == FAIL)
		return (FAIL);
	if (is_eating(pdata) == FAIL)
		return (pdata->common_data.create_status = FAIL, FAIL);
	if (unlock_forks(pdata) == FAIL)
		return (pdata->common_data.create_status = FAIL, FAIL);
	if (is_sleeping(pdata) == FAIL)
		return (pdata->common_data.create_status = FAIL, FAIL);
	if (is_thinking(pdata) == FAIL)
		return (pdata->common_data.create_status = FAIL, FAIL);
	if (*(int *)pdata->philo_nb % 2 == 1)
	{
		if (*(int *)pdata->tte == *(int *)pdata->tts)
			homemade_usleep(pdata, (*(int *)pdata->tte / 2));
		else if (*(int *)pdata->tte > *(int *)pdata->tts)
			homemade_usleep(pdata, ((*(int *)pdata->tte - *(int *)pdata->tts)
					+ (*(int *)pdata->tte / 2)));
	}
	return (SUCCESS);
}

int	three_two_one_gooooo_philo(t_pdata *pdata)
{
	while (1)
	{
		usleep(1 * 100);
		if (get_current_ts(pdata) >= (pdata->ts_0 + 100))
			return (pdata->ts_0 = get_current_ts(pdata), SUCCESS);
	}
	return (FAIL);
}

int	philo_routine_loop(t_pdata *pdata)
{
	usleep(1);
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == YES)
	{
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		return (STOP);
	}
	if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	if (philo_sub_routines(pdata) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

void	*philo_routine(void *content)
{
	t_pdata	*pdata;
	int		*routine_prep_status;

	pdata = (t_pdata *)content;
	if (three_two_one_gooooo_philo(pdata) == FAIL)
		return ((void *)FAIL);
	routine_prep_status = routine_preparation(pdata);
	if (routine_prep_status != (void *)SUCCESS)
		return ((void *)routine_prep_status);
	while (1)
	{
		if (philo_routine_loop(pdata) == FAIL
			|| philo_routine_loop(pdata) == STOP)
		{
			if (philo_routine_loop(pdata) == FAIL)
				return ((void *)FAIL);
			else
				return ((void *)STOP);
		}
	}
	return ((void *)FAIL);
}
