/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:18:03 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/14 13:12:00 by ddyankov         ###   ########.fr       */
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
		usleep(100);
		if (!is_alive(table->philo))
			return (0);
	}
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
void		fifth_argument(t_struct *table)
{
	int	i;

	i = 0;
	if (table->meals_to_eat < 1)
		return ;
	while (i < table->num_philo)
	{
		if (table->eat_count / table->num_philo != table->meals_to_eat)
			return ;
		i++;
	}
	printf("%lld The program ends here ", get_time(table) - table->start_time);
	printf("All have eaten %d times\n", table->meals_to_eat);
}
