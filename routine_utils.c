/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:26:24 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/29 17:11:17 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *p, int odd_or_even)
{
	if (odd_or_even == 0)
	{
		pthread_mutex_lock(&p->table->mut_forks[p->right]);
		pthread_mutex_lock(&p->table->mut_forks[p->left]);
	}
	else
	{
		pthread_mutex_lock(&p->table->mut_forks[p->left]);
		pthread_mutex_lock(&p->table->mut_forks[p->right]);
	}
}

void	unlock_forks(t_philo *p, int odd_or_even)
{
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
}

void	drop_forks(t_philo *p, int odd_or_even)
{
	if (odd_or_even == 0)
	{
		pthread_mutex_lock(&p->table->mut_forks[p->left]);
		p->table->forks[p->left] = 0;
		pthread_mutex_unlock(&p->table->mut_forks[p->left]);
		pthread_mutex_lock(&p->table->mut_forks[p->right]);
		p->table->forks[p->right] = 0;
		pthread_mutex_unlock(&p->table->mut_forks[p->right]);
	}
	else
	{
		pthread_mutex_lock(&p->table->mut_forks[p->right]);
		p->table->forks[p->right] = 0;
		pthread_mutex_unlock(&p->table->mut_forks[p->right]);
		pthread_mutex_lock(&p->table->mut_forks[p->left]);
		p->table->forks[p->left] = 0;
		pthread_mutex_unlock(&p->table->mut_forks[p->left]);
	}
}

void	print_status(t_philo *p, char *status)
{
	pthread_mutex_lock(&p->table->mut_end);
	if (!p->table->end)
	{
		printf("%lld %d %s\n",
			get_time() - p->table->start_t, p->id, status);
	}
	pthread_mutex_unlock(&p->table->mut_end);
}
