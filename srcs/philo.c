/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:21 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 21:26:41 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (are_args_valid(argv, argc) == FAIL)
		return (FAIL);
	set_mallocs_to_null(&philo);
	if (init_values(&philo, argv, argc) == FAIL)
		return (FAIL);
	if (get_starting_ts(&philo) == -1)
		return (FAIL);
	if (create_pthreads(&philo) == FAIL)
		return (FAIL);
	if (join_threads(&philo) == FAIL)
		return (FAIL);
	return (clean_all(&philo), SUCCESS);
}
