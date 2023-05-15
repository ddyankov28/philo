/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:38:02 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/15 15:06:54 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_struct *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				(void *)&table->philo[i]) != 0)
			return (ft_free(table, "Failed to create threads\n"), 0);
	}
	i = -1;
	while (++i < table->num_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (ft_free(table, "Failed to join threads\n"), 0);
	}
	return (1);
}

int	set_mutexes(t_struct *table)
{
	int	i;

	i = -1;
	table->mut_forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->mut_forks)
		return (ft_free(table, "Failed to allocate memory for forks mutexes"),
			0);
	while (++i < table->num_philo)
	{
		if (pthread_mutex_init(&table->mut_forks[i], NULL) != 0)
			return (ft_free(table, "Failed to init forks mutexes"), 0);
	}
	if (pthread_mutex_init(&table->mut_print, NULL) != 0)
		return (ft_free(table, "Failed to init print mutex"), 0);
	if (pthread_mutex_init(&table->mut_end, NULL) != 0)
		return (ft_free(table, "Failed to init dead mutex"), 0);
	return (1);
}

int	set_table(t_struct *table, char **av)
{
	int	i;

	table->num_philo = ft_atoi(av[1]);
	table->t_to_die = ft_atoi(av[2]);
	table->t_to_eat = ft_atoi(av[3]);
	table->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	if (!table->num_philo || !table->t_to_die || !table->t_to_eat
		|| !table->t_to_sleep)
		return (ft_free(table, "Invalid arguments"), 0);
	table->end = 0;
	table->start_t = get_time();
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		return (ft_free(table, "Philo Malloc failed"), 0);
	table->forks = malloc(sizeof(int) * table->num_philo);
	if (!table->forks)
		return (ft_free(table, "Forks Malloc failed"), 0);
	i = -1;
	while (++i < table->num_philo)
		table->forks[i] = 0;
	return (1);
}

void	set_philo(t_struct *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].left = i;
		philo[i].right = (i + 1) % table->num_philo;
		philo[i].eat_count = 0;
		philo[i].table = table;
		philo[i].last_eat = get_time();
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
	if (!set_table(table, av))
		return (1);
	set_philo(table, table->philo);
	if (!set_mutexes(table))
		return (1);
	if (table->num_philo == 1)
	{
		if (!one_philo_thread(table))
			return (1);
		else
			return (ft_free(table, NULL), 0);
	}
	if (!create_threads(table))
		return (1);
	fifth_argument(table);
	ft_free(table, NULL);
	return (0);
}
