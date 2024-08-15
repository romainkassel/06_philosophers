/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/08 16:36:49 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_args_bigger_than_0(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			if (i == 1)
				print_mess(NULL, 1, E_NEG_OR_NULL_PHILO, FAIL);
			else
				print_mess(NULL, 1, E_NEG_OR_NULL_TS, FAIL);
			return (FAIL);
		}
		i++;
	}
	if (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
		{
			print_mess(NULL, 1, E_NEG_MEALS, FAIL);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	are_there_only_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (print_mess(NULL, 1, E_NO_DIGITS, FAIL), FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	is_count_correct(int argc)
{
	if (argc < 5 || argc > 6)
		return (print_mess(NULL, 1, E_INV_PARAM, FAIL), FAIL);
	return (SUCCESS);
}

int	check_short_int_max(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) > SHRT_MAX)
			return (print_mess(NULL, 1, E_SHORT_INT_MAX, FAIL), FAIL);
		i++;
	}
	return (SUCCESS);
}

int	are_args_valid(char **argv, int argc)
{
	if (are_there_only_digits(argv) == FAIL
		|| check_short_int_max(argv) == FAIL
		|| are_args_bigger_than_0(argv) == FAIL
		|| is_count_correct(argc) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
