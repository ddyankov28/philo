/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:05 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/13 10:33:12 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    is_alive(t_philo *p)
{
    pthread_mutex_lock(&p->table->mut_dead);
    if (p->table->dead || p->eat_count == p->table->meals_to_eat)
    {
        p->done = 1;
        pthread_mutex_unlock(&p->table->mut_dead);
        return (0);
    }
    if (get_time(p->table) - p->last_eat >= p->table->time_to_die && !p->table->dead)
    {
        pthread_mutex_unlock(&p->table->mut_dead);
        print_status(p, "died");
        pthread_mutex_lock(&p->table->mut_dead);
        p->table->dead = 1;
        p->done = 1;
        pthread_mutex_unlock(&p->table->mut_dead);
        return (0);
    }
    pthread_mutex_unlock(&p->table->mut_dead);
    return (1);
}

int     sleep_think(t_philo *p)
{
    if (!is_alive(p))
        return (0);
    print_status(p, "sleep");
    if (!time_update(p->table->time_to_sleep, p->table))
        return (0);
    if (!is_alive(p))
        return (0);
    print_status(p, "think");
    time_update(1, p->table);
    return (1);
}

void    drop_forks(t_philo *p, int odd_or_even)
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
/* 1. Update the forks, so that we know they are already taken
   2. Unlock the forks again in a specific way, depends how you took them
   3. Check if still alive
   4. Print the messages and update last time eaten
   5. Sleep for an exact time increase eat counter 
*/
int try_eat(t_philo *p, int odd_or_even)
{
    p->table->forks[p->right] = p->id;
    p->table->forks[p->left] = p->id;
    //printf("PHILO %d LEFT %d  and RIGHT %d\n",p->id, p->left, p->right);
    //printf("PHILO %d LEFT %d  and RIGHT %d\n",p->id, p->table->forks[p->left], p->table->forks[p->right]);
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
    print_status(p, "fork");
    print_status(p, "fork");
    print_status(p, "eat");
    p->last_eat = get_time(p->table);
    if (!time_update(p->table->time_to_eat, p->table))
        return (0);
    p->eat_count++;
    return (1);
}

void    lock_forks(t_philo *p, int odd_or_even)
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
void    unlock_forks(t_philo *p, int odd_or_even)
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

/* 1. Check if alive
   2. Lock the forks and if the ID is even lock furst the right,
      else lock the left 
   3. Check if forks are available 
   4. try to eat, later drop forks after succesfull eat and sleep
   5. els if forks are not available unlock them and check if alive again 
*/
int     start(t_philo *p)
{
    if (!is_alive(p))
        return (0);
    lock_forks(p,p->id % 2);
    if (p->table->forks[p->right] == 0
		&& p->table->forks[p->left] == 0)
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
		unlock_forks(p,p->id % 2);
		if (!is_alive(p))
			return (0);
	}
	return (1);
}

void    print_status(t_philo *p, char *status)
{
    pthread_mutex_lock(&p->table->mut_dead);
    pthread_mutex_lock(&p->table->mut_print);
    if (!p->done && !p->table->dead && p->eat_count != p->table->meals_to_eat)
    {
        if (ft_strcmp(status ,"fork") == 0)
            printf("%lld %d has taken a fork\n", get_time(p->table) - p->table->start_time, p->id);
        else if (ft_strcmp(status ,"eat") == 0)
            printf("%lld %d is eating\n", get_time(p->table) - p->table->start_time, p->id);
        else if (ft_strcmp(status ,"sleep") == 0)
            printf("%lld %d is sleeping\n", get_time(p->table) - p->table->start_time, p->id);
        else if (ft_strcmp(status ,"think") == 0)
            printf("%lld %d is thinking\n", get_time(p->table) - p->table->start_time, p->id);
        else if (ft_strcmp(status ,"died") == 0)
            printf("%lld %d died\n", get_time(p->table) - p->table->start_time, p->id);
    }
    pthread_mutex_unlock(&p->table->mut_print);
    pthread_mutex_unlock(&p->table->mut_dead);
}
void    *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *) arg;
    while (!p->done)
    {
        if (p->eat_count == p->table->meals_to_eat)
            break ;
        pthread_mutex_lock(&p->table->mut_dead);
        if (p->table->dead)
        {
            pthread_mutex_unlock(&p->table->mut_dead);
            return NULL;            
        }
        pthread_mutex_unlock(&p->table->mut_dead);
        if (!start(p))
            return (NULL);
    }
    return NULL;
}


