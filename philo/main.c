/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:03:33 by gmorais-          #+#    #+#             */
/*   Updated: 2023/10/03 13:52:08 by gmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tudo	*tudo(void)
{
	static t_tudo	tudo;

	return (&tudo);
}

int	checknum(char *arg)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = "0123456789";
	i = -1;
	if (!arg)
		return (-1);
	while (arg[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (arg[i] == str[j])
				break ;
		}
		if (arg[i] == str[j])
			continue ;
		return (-1);
	}
	return (0);
}

int	cleiton(int ac, char **av)
{
	tudo()->n_philo = ft_atoi(av[1]);
	tudo()->t_die = ft_atoi(av[2]) * 1000;
	tudo()->t_eat = ft_atoi(av[3]) * 1000;
	tudo()->t_sleep = ft_atoi(av[4]) * 1000;
	tudo()->start = tempo_real();
	if (ac == 6)
		tudo()->time_eat = ft_atoi(av[5]);
	else
		tudo()->time_eat = -1;
	if (tudo()->n_philo <= 0 || tudo()->t_die <= 0 \
		|| tudo()->t_eat <= 0 || tudo()->t_sleep <= 0)
	{
		printf("Error: numero de parametros\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = ac - 1;
	if (ac == 5 || ac == 6)
	{
		while (i > 0)
		{
			if (checknum(av[i--]) == -1)
			{
				printf("error\n");
				return (0);
			}
		}
		if (cleiton(ac, av) == 0)
		{
			aloca_tudo();
			ft_clean();
		}
	}
	else
		printf("Error: numero de argumentos\n");
	return (0);
}
