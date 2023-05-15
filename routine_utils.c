/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:26:24 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/15 17:57:11 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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
	pthread_mutex_lock(&p->table->mut_print);
	pthread_mutex_lock(&p->table->mut_end);
	if (!p->table->end)
	{
		if (ft_strcmp(status, "fork") == 0)
			printf("%lld %d has taken a 🍴fork🍴\n",
				get_time() - p->table->start_t, p->id);
		else if (ft_strcmp(status, "eat") == 0)
			printf("%lld %d is 🍜eating🍜\n",
				get_time() - p->table->start_t, p->id);
		else if (ft_strcmp(status, "sleep") == 0)
			printf("%lld %d is 🛌sleeping🛌\n",
				get_time() - p->table->start_t, p->id);
		else if (ft_strcmp(status, "think") == 0)
			printf("%lld %d is 🤔thinking🤔\n",
				get_time() - p->table->start_t, p->id);
		else if (ft_strcmp(status, "died") == 0)
			printf("%lld %d 💀died💀\n",
				get_time() - p->table->start_t, p->id);
	}
	pthread_mutex_unlock(&p->table->mut_end);
	pthread_mutex_unlock(&p->table->mut_print);
}
