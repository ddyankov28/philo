/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:15:31 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/15 17:48:09 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	printf("%d 1 has taken a 🍴fork🍴\n", 0);
	usleep(p->table->t_to_die * 1000);
	printf("%d 1 has 💀died💀\n", p->table->t_to_die);
	return (NULL);
}

int	one_philo_thread(t_struct *table)
{
	pthread_t	p1;

	if (pthread_create(&p1, NULL, &one_philo, (void *)&table->philo[0]) != 0)
		return (ft_free(table, "Failed to create a thread for one philo"), 0);
	if (pthread_join(p1, NULL) != 0)
		return (ft_free(table, "Failed to join a thread for one philo"), 0);
	return (1);
}
