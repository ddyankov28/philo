/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:18:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/29 17:32:25 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_struct *table, char *message)
{
	int	i;

	i = -1;
	if (message)
		printf("%s\n", message);
	if (table->philo)
		free(table->philo);
	if (table->forks)
		free(table->forks);
	if (table->mut_forks)
	{
		while (++i < table->num_philo)
			pthread_mutex_destroy(&table->mut_forks[i]);
		free(table->mut_forks);
	}
	pthread_mutex_destroy(&table->mut_end);
	if (table)
		free(table);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	time_update(long long time_to_pass, t_struct *table)
{
	if (!is_alive(table->philo))
		return (0);
	usleep(time_to_pass * 1000);
	return (1);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		a;

	result = 0;
	a = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-')
		return (0);
	if (str[a] == '+')
	{
		a++;
		if (str[a] < '0' || str[a] > '9')
			return (0);
	}
	while ((str[a]) >= '0' && str[a] <= '9')
	{
		result = result * 10 + str[a] - 48;
		a++;
		if (result > 2147483647 || result < 1)
			return (0);
	}
	if (str[a] != '\0')
		return (0);
	return (result);
}

void	fifth_argument(t_struct *table)
{
	int	i;

	i = 0;
	if (table->meals_to_eat < 1)
		return ;
	while (i < table->num_philo)
	{
		if (table->philo[i].eat_count != table->meals_to_eat)
			return ;
		i++;
	}
	printf("%lld ⛔️⛔️⛔️The program ", get_time() - table->start_t);
	printf("ends here⛔️⛔️⛔️ ");
	printf("All have eaten %d times\n", table->meals_to_eat);
}
