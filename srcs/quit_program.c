/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:42:22 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_mess(t_pdata *pdata, int i, char *mess, int status)
{
	if (pdata)
		if (pthread_mutex_lock(pdata->write_action_m) != 0)
			return (print_mess(pdata, 1, E_MUT_L, FAIL), FAIL);
	if (status == FAIL)
	{
		if (i == 1)
			ft_putstr_fd("Error\n", 2);
		if (status)
			(ft_putstr_fd(mess, 2), ft_putstr_fd("\n", 2));
	}
	else
	{
		if (i == 1)
			ft_putstr_fd("Success\n", 1);
		if (status)
			(ft_putstr_fd(mess, 1), ft_putstr_fd("\n", 1));
	}
	if (pdata)
		if (pthread_mutex_unlock(pdata->write_action_m) != 0)
			return (print_mess(pdata, 1, E_MUT_U, FAIL), FAIL);
	return (SUCCESS);
}

void	clean_all(t_philo *philo)
{
	if (philo->threads)
		(free(philo->threads), philo->threads = NULL);
	destroy_mutexes(philo);
	if (philo->forks)
		(free(philo->forks), philo->forks = NULL);
	if (philo->common_data.stop_simul_m)
		(free(philo->common_data.stop_simul_m),
			philo->common_data.stop_simul_m = NULL);
	if (philo->common_data.meal_nb)
		(free(philo->common_data.meal_nb),
			philo->common_data.meal_nb = NULL);
	if (philo->common_data.last_meal)
		(free(philo->common_data.last_meal),
			philo->common_data.last_meal = NULL);
	if (philo->pdata)
		(free(philo->pdata), philo->pdata = NULL);
}

void	quit_program(t_philo *philo, int i, char *mess, int status)
{
	print_mess(philo->pdata, i, mess, status);
	clean_all(philo);
}
