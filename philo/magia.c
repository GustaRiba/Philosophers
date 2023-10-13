/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:06:11 by gmorais-          #+#    #+#             */
/*   Updated: 2023/10/03 14:15:51 by gmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	aloca_tudo(void)
{
	int	n_philo;

	n_philo = tudo()->n_philo;
	tudo()->philo = (t_philo *)malloc(sizeof(t_philo) * n_philo);
	tudo()->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* n_philo);
	if (!tudo()->philo || !tudo()->fork_mutex)
	{
		printf("Error: malloc\n");
		return ;
	}
	pthread_mutex_init(&tudo()->print, NULL);
	pthread_mutex_init(&tudo()->dead_mutex, NULL);
	pthread_mutex_init(&tudo()->eat, NULL);
	nascimento_philo();
}

void	acoes(t_philo *philo)
{
	int	right;
	int	left;

	left = philo->id;
	right = (left + 1) % philo->n_philo;
	pegar_garfo(philo, left, right);
	philo_comer(philo);
	pthread_mutex_unlock(&tudo()->fork_mutex[left]);
	pthread_mutex_unlock(&tudo()->fork_mutex[right]);
	philo_dormir(philo);
	philo_pensar(philo);
}

void	pegar_garfo(t_philo *philo, int rigth, int left)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&tudo()->fork_mutex[left]);
		action(philo->id, "has taken a fork");
		pthread_mutex_lock(&tudo()->fork_mutex[rigth]);
		action(philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&tudo()->fork_mutex[rigth]);
		action(philo->id, "has taken a fork");
		pthread_mutex_lock(&tudo()->fork_mutex[left]);
		action(philo->id, "has taken a fork");
	}
}

void	*principal(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	ft_wait();
	if (tudo()->n_philo == 1)
		philo_pensar(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!morte_philo(philo, 0))
	{
		if (philo->time_eat == 0)
			break ;
		else if (philo->n_philo > 1)
			acoes(philo);
	}
	return (NULL);
}

void	nascimento_philo(void)
{
	int	i;
	int	j;
	int	n_philo;

	i = -1;
	j = -1;
	n_philo = tudo()->n_philo;
	while (++i < n_philo)
	{
		tudo()->philo[i].id = i;
		tudo()->philo[i].n_philo = n_philo;
		tudo()->philo[i].time_eat = tudo()->time_eat;
		tudo()->philo[i].last_eat = tempo_real();
	}
	i = 0;
	while (++j < n_philo)
		pthread_mutex_init(&tudo()->fork_mutex[i++], NULL);
	i = -1;
	while (++i < n_philo)
	{
		pthread_create(&(tudo()->philo[i].thread), NULL, &principal,
			(void *)&tudo()->philo[i]);
	}
	verify_deaths();
}
