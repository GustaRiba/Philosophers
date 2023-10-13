/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:05:41 by gmorais-          #+#    #+#             */
/*   Updated: 2023/10/03 14:16:33 by gmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	int		a;
	long	nb;

	a = 0;
	nb = 0;
	if (nptr[a] == '+')
		a++;
	while (nptr[a])
	{
		if ((nptr[a] < '0' && nptr[a] > '9') || nptr[a] == 'r')
			return (-1);
		nb = (nb * 10) + (nptr[a] - 48);
		a++;
	}
	return (nb);
}

void	ft_wait(void)
{
	long	i;

	i = tudo()->start - tempo_real();
	if (i > 0)
		usleep(i);
}

long	tempo_real(void)
{
	struct timeval	val;

	gettimeofday(&val, 0);
	return (val.tv_sec * 1000000L + val.tv_usec);
}

void	action(int id, char *action)
{
	pthread_mutex_lock(&(tudo()->print));
	if (morte_philo(&tudo()->philo[id], 1))
	{
		pthread_mutex_unlock(&(tudo()->print));
		return ;
	}
	printf("%ld\t%d\t%s\n", ((tempo_real() - tudo()->start))
		/ 1000, id + 1, action);
	pthread_mutex_unlock(&(tudo()->print));
}

void	ft_clean(void)
{
	int	i;
	int	n_philo;

	i = -1;
	n_philo = tudo()->n_philo;
	while (++i < n_philo)
		pthread_mutex_destroy(&tudo()->fork_mutex[i]);
	pthread_mutex_destroy(&tudo()->print);
	pthread_mutex_destroy(&tudo()->dead_mutex);
	pthread_mutex_destroy(&tudo()->eat);
	free(tudo()->fork_mutex);
	free(tudo()->philo);
}
