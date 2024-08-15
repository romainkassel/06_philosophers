/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:28:03 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philo *philo)
{
	philo->threads
		= (pthread_t *)ft_calloc(sizeof(pthread_t), philo->philo_nb + 1);
	if (!philo->threads)
		return (quit_program(philo, 1, E_FAILED_MALLOC, FAIL), FAIL);
	return (SUCCESS);
}

int	create_pthreads(t_philo *philo)
{
	int	i;

	if (pthread_create(&philo->threads[philo->philo_nb],
			NULL, big_brother, philo) == FAIL)
		return (quit_program(philo, 1, E_PTHREAD_CREATE, FAIL), FAIL);
	i = 0;
	while (i < philo->philo_nb)
	{
		if (pthread_create(&philo->threads[i],
				NULL, philo_routine, &philo->pdata[i]) == FAIL)
			return (quit_program(philo, 1, E_PTHREAD_CREATE, FAIL), FAIL);
		i++;
	}
	return (SUCCESS);
}

int	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i <= philo->philo_nb)
	{
		if (pthread_join(philo->threads[i], NULL) != 0)
			return (quit_program(philo, 1, E_PTHREAD_JOIN, FAIL), FAIL);
		i++;
	}
	return (SUCCESS);
}
