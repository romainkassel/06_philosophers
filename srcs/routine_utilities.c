/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:42:57 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	homemade_usleep(t_pdata *pdata, int time_in_ms)
{
	int	starting_ts;

	starting_ts = get_current_ts(pdata);
	usleep((time_in_ms - (time_in_ms / 4)) * 1000);
	while (get_current_ts(pdata) < (starting_ts + time_in_ms))
		usleep(10);
	return (SUCCESS);
}

int	write_act(t_pdata *pdata, int id, char *act, int ts_0)
{
	if (pthread_mutex_lock(pdata->write_action_m) != 0)
		return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	printf("%d %d %s\n", get_current_ts(pdata) - ts_0, id, act);
	if (pthread_mutex_unlock(pdata->write_action_m) != 0)
		return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

int	get_total_ms(struct timeval *time)
{
	long long int		seconds_to_microseconds;
	long long int		total_microseconds;
	long long int		microseconds_to_ms;

	seconds_to_microseconds = time->tv_sec * 1e+6;
	total_microseconds = seconds_to_microseconds + time->tv_usec;
	microseconds_to_ms = total_microseconds / 1000;
	return (microseconds_to_ms);
}

int	get_starting_ts(t_philo *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (quit_program(philo, 1, E_GET_TOTD, FAIL), -1);
	if (pthread_mutex_lock(philo->ms_start_m) != 0)
		return (print_mess(philo->pdata, 1, E_MUT_L, FAIL), FAIL);
	*(int *)philo->ms_start = get_total_ms(&time);
	if (pthread_mutex_unlock(philo->ms_start_m) != 0)
		return (print_mess(philo->pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

int	get_current_ts(t_pdata *pdata)
{
	struct timeval	time;
	int				current_ts_in_ms;

	if (gettimeofday(&time, NULL) == -1)
		return (print_mess(pdata, 1, E_GET_TOTD, FAIL), -1);
	current_ts_in_ms = get_total_ms(&time);
	return (current_ts_in_ms);
}
