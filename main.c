/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:38:02 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/04 17:44:38 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_table(t_struct *table, char **av)
{
	table->num_philo = ft_atoi(av[1], table);
	table->time_to_die = ft_atoi(av[2], table);
	table->time_to_eat = ft_atoi(av[3], table);
	table->time_to_sleep = ft_atoi(av[4], table);
	if (av[5])
		table->meals_to_eat = ft_atoi(av[5], table);
	else
		table->meals_to_eat = -1;
	table->start_time = get_time(table);
	table->done = 0;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		ft_free(table, "Philo Malloc failed");
	table->forks = malloc(sizeof(int) * table->num_philo);
	if (!table->forks)
		ft_free(table, "Forks Malloc failed");
}

void	set_philo(t_struct *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].left = i;
		philo[i].right = (i + 1) % table->num_philo;
		philo[i].table = table;
		philo[i].eat_count = 0;
		philo[i].is_eating = 0;
		philo[i].last_eat = get_time(table);
		philo[i].time_limit = philo[i].last_eat + table->time_to_die;
		i++;
	}
}
int	main(int ac, char **av)
{
	t_struct	*table;

	if (ac < 5 || ac > 6)
		return (printf("Invalind number of arguments!\n"), 1);
	table = malloc(sizeof(t_struct));
	if (!table)
		return (printf("Failed to allocate memory for struct\n"), 1);
	set_table(table, av);
	set_philo(table, table->philo);
	set_mutexes(table);
	if (table->num_philo == 1)
		one_philo_thread(table);
	create_threads(table);
	return (0);
}
