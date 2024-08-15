/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:21 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:37:57 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simul_status_and_write(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (write_act(pdata, pdata->id, "has taken a fork",
				pdata->ts_0) == FAIL)
		{
			if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
				return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
			return (FAIL);
		}
	}
	if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

int	has_taken_a_fork_left(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		if (pthread_mutex_lock(pdata->left_fork_m) != 0)
			return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
		if (check_simul_status_and_write(pdata) == FAIL)
			return (FAIL);
	}
	else
	{
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		pdata->locked_left_fork = 0;
	}
	return (SUCCESS);
}

int	has_taken_a_fork_right(t_pdata *pdata)
{
	if (pthread_mutex_lock(pdata->stop_simul_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (pdata->stop_simul == NOT_YET)
	{
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		if (pthread_mutex_lock(pdata->right_fork_m) != 0)
			return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
		if (check_simul_status_and_write(pdata) == FAIL)
			return (FAIL);
	}
	else
	{
		if (pthread_mutex_unlock(pdata->stop_simul_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		pdata->locked_right_fork = 0;
	}
	return (SUCCESS);
}

int	unlock_forks(t_pdata *pdata)
{
	if (pdata->id % 2 == 1)
	{
		if (pdata->locked_left_fork == 1)
			if (pthread_mutex_unlock(pdata->left_fork_m) != 0)
				return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		if (pdata->locked_right_fork == 1)
			if (pthread_mutex_unlock(pdata->right_fork_m) != 0)
				return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	}
	else
	{
		if (pdata->locked_right_fork == 1)
			if (pthread_mutex_unlock(pdata->right_fork_m) != 0)
				return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
		if (pdata->locked_left_fork == 1)
			if (pthread_mutex_unlock(pdata->left_fork_m) != 0)
				return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	}
	return (SUCCESS);
}

int	take_forks_depending_on_id(t_pdata *pdata)
{
	if (pdata->id % 2 == 0)
	{
		if (has_taken_a_fork_left(pdata) == FAIL)
			return (pdata->common_data.create_status = FAIL, FAIL);
		if (has_taken_a_fork_right(pdata) == FAIL)
			return (pdata->common_data.create_status = FAIL, FAIL);
	}
	else
	{
		if (has_taken_a_fork_right(pdata) == FAIL)
			return (pdata->common_data.create_status = FAIL, FAIL);
		if (has_taken_a_fork_left(pdata) == FAIL)
			return (pdata->common_data.create_status = FAIL, FAIL);
	}
	return (SUCCESS);
}
