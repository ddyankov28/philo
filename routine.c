/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:05 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/29 16:36:00 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *p)
{
	if (get_time() - p->last_eat >= p->table->t_to_die)
	{
		print_status(p, "died");
		pthread_mutex_lock(&p->table->mut_end);
		p->table->end = 1;
		pthread_mutex_unlock(&p->table->mut_end);
		return (0);
	}
	return (1);
}

int	sleep_think(t_philo *p)
{
	if (!is_alive(p))
		return (0);
	print_status(p, "is sleeping");
	if (p->eat_count == p->table->meals_to_eat)
		return (0);
	if (!time_update(p->table->t_to_sleep, p->table))
		return (0);
	if (!is_alive(p))
		return (0);
	print_status(p, "is thinking");
	if (!time_update(1, p->table))
		return (0);
	return (1);
}

int	try_eat(t_philo *p, int odd_or_even)
{
	p->table->forks[p->right] = p->id;
	p->table->forks[p->left] = p->id;
	if (odd_or_even == 0)
	{
		pthread_mutex_unlock(&p->table->mut_forks[p->left]);
		pthread_mutex_unlock(&p->table->mut_forks[p->right]);
	}
	else
	{
		pthread_mutex_unlock(&p->table->mut_forks[p->right]);
		pthread_mutex_unlock(&p->table->mut_forks[p->left]);
	}
	if (!is_alive(p))
		return (0);
	print_status(p, "has taken a fork");
	print_status(p, "has taken a fork");
	print_status(p, "is eating");
	p->last_eat = get_time();
	if (!time_update(p->table->t_to_eat, p->table))
		return (0);
	p->eat_count++;
	return (1);
}

int	start(t_philo *p)
{
	if (!is_alive(p))
		return (0);
	lock_forks(p, p->id % 2);
	if (p->table->forks[p->right] == 0 && p->table->forks[p->left] == 0)
	{
		if (!try_eat(p, p->id % 2))
			return (0);
		drop_forks(p, p->id % 2);
		if (!sleep_think(p))
			return (0);
		return (1);
	}
	else
	{
		unlock_forks(p, p->id % 2);
		if (!is_alive(p))
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (p->eat_count != p->table->meals_to_eat)
	{
		pthread_mutex_lock(&p->table->mut_end);
		if (p->table->end == 1)
		{
			pthread_mutex_unlock(&p->table->mut_end);
			return (NULL);
		}
		pthread_mutex_unlock(&p->table->mut_end);
		if (!start(p))
			return (NULL);
	}
	return (NULL);
}
