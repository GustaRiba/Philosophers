/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:48 by gmorais-          #+#    #+#             */
/*   Updated: 2023/10/03 14:25:08 by gmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_comer(t_philo *philo)
{
	action(philo->id, "is eating");
	pthread_mutex_lock(&(tudo()->dead_mutex));
	philo->last_eat = tempo_real();
	pthread_mutex_unlock(&(tudo()->dead_mutex));
	usleep(tudo()->t_eat);
	pthread_mutex_lock(&(tudo()->eat));
	if (philo->time_eat > 0)
		philo->time_eat--;
	pthread_mutex_unlock(&(tudo()->eat));
}

void	philo_dormir(t_philo *philo)
{
	if (philo->time_eat == 0)
		return ;
	action(philo->id, "is sleeping");
	usleep(tudo()->t_sleep);
}

void	philo_pensar(t_philo *philo)
{
	long	i;

	if (philo->time_eat == 0)
		return ;
	action(philo->id, "is thinking");
	if (tudo()->n_philo % 2 == 1 && tudo()->t_die <= (tudo()->t_eat * 3))
		i = tudo()->t_die - (tudo()->t_sleep + (tudo()->t_eat));
	else if (tudo()->n_philo % 2 == 0 && tudo()->t_die <= (tudo()->t_eat * 2))
		i = tudo()->t_die - (tudo()->t_sleep + (tudo()->t_eat));
	else
	{
		i = tudo()->t_die - (tempo_real() - philo->last_eat) \
		- (tudo()->t_eat / 2);
		if (i < 0)
			i = 0;
	}
	usleep(i);
}

void	verify_deaths(void)
{
	int	n_philo;
	int	i;

	ft_wait();
	n_philo = tudo()->n_philo;
	i = -1;
	while (++i < n_philo)
		pthread_join(tudo()->philo[i].thread, NULL);
}

int	morte_philo(t_philo *philo, int flag)
{
	if (!flag)
		pthread_mutex_lock(&(tudo()->print));
	pthread_mutex_lock(&(tudo()->dead_mutex));
	if (tudo()->dead == 1)
	{
		pthread_mutex_unlock(&(tudo()->dead_mutex));
		if (!flag)
			pthread_mutex_unlock(&(tudo()->print));
		return (1);
	}
	if (tempo_real() - philo->last_eat >= tudo()->t_die)
	{
		printf("%ld\t%i\t%s\n", ((tempo_real() - tudo()->start) / 1000),
			philo->id, "morreu");
		tudo()->dead = 1;
		pthread_mutex_unlock(&(tudo()->dead_mutex));
		if (!flag)
			pthread_mutex_unlock(&(tudo()->print));
		return (1);
	}
	pthread_mutex_unlock(&(tudo()->dead_mutex));
	if (!flag)
		pthread_mutex_unlock(&(tudo()->print));
	return (0);
}
