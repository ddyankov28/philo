/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:18:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/13 10:16:02 by ddyankov         ###   ########.fr       */
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

long long	get_time(t_struct *table)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_free(table, "Error by function gettimeofday");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	time_update(long long time_to_pass, t_struct *table)
{
	long long curr_time;

	curr_time = get_time(table);
	if (!is_alive(table->philo))
		return (0);
	while (get_time(table) - curr_time < time_to_pass)
	{
		usleep(10);
		if (!is_alive(table->philo))
			return (0);
	}
	return (1);
}
int	ft_atoi(const char *str, t_struct *table)
{
	long	result;
	int		a;

	result = 0;
	a = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-')
			ft_free(table, "Negative numbers are not allowed");
	if (str[a] == '+')
	{
		a++;
		if (str[a] < '0' || str[a] > '9')
			ft_free(table, "Please insert only digits");
	}
	while ((str[a]) >= '0' && str[a] <= '9')
	{
		result = result * 10 + str[a] - 48;
		a++;
		if (result > 2147483647 || result < 1)
			ft_free(table, "Not a valid integer");
	}
	if (str[a] != '\0')
		ft_free(table, "Try only with integers");
	return (result);
}
void		fifth_argument(t_struct *table)
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
	printf("TEST\n");
	pthread_mutex_lock(&table->mut_print);
	printf("%lld The program ends here ", get_time(table) - table->start_time);
	printf("All have eaten %d times\n", table->meals_to_eat);
	pthread_mutex_unlock(&table->mut_print);
}
