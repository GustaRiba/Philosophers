/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:04:01 by gmorais-          #+#    #+#             */
/*   Updated: 2023/10/03 14:15:35 by gmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct philo
{
	int							id;
	int							n_philo;
	int							time_eat;
	long						last_eat;
	pthread_t					thread;

}		t_philo;

typedef struct tudo
{
	int							time_eat;
	int							n_philo;
	int							dead;
	int							t_die;
	int							t_eat;
	long						think_time;
	int							t_sleep;
	long						start;
	t_philo						*philo;
	pthread_mutex_t				eat;
	pthread_mutex_t				print;
	pthread_mutex_t				dead_mutex;
	pthread_mutex_t				*fork_mutex;
}			t_tudo;

//utils

void			error(void);
void			ft_wait(void);
long			tempo_real(void);
long			ft_atoi(const char *nptr);
t_tudo			*tudo(void);
void			action(int id, char *action);
void			ft_clean(void);

//magia

void			pegar_garfo(t_philo *philo, int rigth, int left);
void			*principal(void *ptr);
void			nascimento_philo(void);
void			acoes(t_philo *philo);
void			aloca_tudo(void);

//actions
void			verify_deaths(void);
int				morte_philo(t_philo *philo, int flag);
void			philo_comer(t_philo *id);
void			philo_dormir(t_philo *id);
void			philo_pensar(t_philo *philo);

#endif