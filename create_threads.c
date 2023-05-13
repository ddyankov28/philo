/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:46:22 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/12 10:40:56 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_mutexes(t_struct *table)
{
    int i;

    i = 0;
    
    table->mut_forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
    if (!table->mut_forks)
        ft_free(table, "Failed to allocate memory for forks mutexes");
    while (i < table->num_philo)
    {
        if (pthread_mutex_init(&table->mut_forks[i], NULL) != 0)
            ft_free(table, "Failed to init forks mutexes");
        i++;
    }
    if (pthread_mutex_init(&table->mut_print, NULL) != 0)
        ft_free(table, "Failed to init print mutex");
    if (pthread_mutex_init(&table->mut_dead, NULL) != 0)
        ft_free(table, "Failed to init dead mutex");
}

void    create_threads(t_struct *table)
{
    int i;

    i = 0;
    while (i < table->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &routine, (void *)&table->philo[i]) != 0)
            ft_free(table, "Failed to create threads\n");
        i++;
	}
    i = 0;
    while (i < table->num_philo)
    {
        if (pthread_join(table->philo[i].thread, NULL) != 0)
            ft_free(table, "Failed to join threads\n");
        i++;
    }
}
