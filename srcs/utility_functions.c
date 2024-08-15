/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:08:07 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/07 18:32:16 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;

	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	i = 0;
	while ((*str == '-' || *str == '+')
		&& (*(str + 1) != '-' && *(str + 1) != '+'))
	{
		if (*str == '-')
			i += 1;
		str++;
	}
	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	if (i % 2 == 1)
		nb *= -1;
	return (nb);
}

long int	ft_atol(const char *str)
{
	long int	nb;
	int			i;

	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	i = 0;
	while ((*str == '-' || *str == '+')
		&& (*(str + 1) != '-' && *(str + 1) != '+'))
	{
		if (*str == '-')
			i += 1;
		str++;
	}
	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	if (i % 2 == 1)
		nb *= -1;
	return (nb);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
	{
		*(unsigned char *)s = '\0';
		s++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && count > (UINT_MAX / size))
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	if (size == 0 || count == 0)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}
