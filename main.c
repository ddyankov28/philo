/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:38:02 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/14 13:12:33 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_struct *table)
{
	int	i;

	i = 0;
	while (++i <= table->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				(void *)&table->philo[i]) != 0)
		{
			ft_free(table, "Failed to create threads\n");
			return (1);
		}
	}
	i = 0;
	while (++i <= table->num_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
		{
			ft_free(table, "Failed to join threads\n");
			return (1);
		}
	}
	return (0);
}

int	set_mutexes(t_struct *table)
{
	int	i;

	i = 0;
	table->mut_forks = malloc(sizeof(pthread_mutex_t) * table->num_philo); // 4th maalloc //
	if (!table->mut_forks)
		return (ft_free(table, "Failed to allocate memory for forks mutexes"), 0);
	while (++i <= table->num_philo)
	{
		if (pthread_mutex_init(&table->mut_forks[i], NULL) != 0)
			return (ft_free(table, "Failed to init forks mutexes"),0);
	}
	if (pthread_mutex_init(&table->mut_print, NULL) != 0)
		return (ft_free(table, "Failed to init print mutex"),0);
	if (pthread_mutex_init(&table->mut_end, NULL) != 0)
		return (ft_free(table, "Failed to init dead mutex"), 0);
	return (1);
}

int	set_table(t_struct *table, char **av)
{
	table->num_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->eat_count = 0;
	if (av[5])
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	if (!table->num_philo || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_sleep)
		return (ft_free(table, "Invalid arguments"), 0);
	table->end = 0;
	table->start_time = get_time(table);
	table->philo = malloc(sizeof(t_philo) * table->num_philo); // 2nd malloc //
	if (!table->philo)
		return (ft_free(table, "Philo Malloc failed"),0);
	table->forks = malloc(sizeof(int) * table->num_philo); // 3rd malloc //
	if (!table->forks)
		return (ft_free(table, "Forks Malloc failed"),0);
	return (1);
}

void	set_philo(t_struct *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].left = i;
		philo[i].right = (i + 1) % table->num_philo;
		philo[i].table = table;
		philo[i].last_eat = get_time(table);
	}
}
int	main(int ac, char **av)
{
	t_struct	*table;

	if (ac < 5 || ac > 6)
		return (printf("Invalind number of arguments!\n"), 1);
	table = malloc(sizeof(t_struct)); // 1st malloc //
	if (!table)
		return (printf("Failed to allocate memory for struct\n"), 1);
	if (!set_table(table, av))
		return (1);
	set_philo(table, table->philo);
	if (!set_mutexes(table))
		return (1);
	if (table->num_philo == 1)
		one_philo_thread(table);
	create_threads(table);
	fifth_argument(table);
	return (0);
}
