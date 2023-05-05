/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:05 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/05 11:36:37 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_status(t_philo *p, char *status)
{
    pthread_mutex_lock(&p->table->mut_print);
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
    else if (ft_strcmp(status ,"finish") == 0)
        printf("%lld Philos have eaten %d times\n", get_time(p->table) - p->table->start_time, p->table->meals_to_eat);
    pthread_mutex_unlock(&p->table->mut_print);
}
void is_alive(t_philo *p)
{
    if (p->is_eating == 0 && get_time(p->table) > p->time_limit)
    {
        print_status(p, "died");
            ft_free_no_message(p->table);
    }
}

void    drop_forks(t_philo *p)
{
    pthread_mutex_lock(&p->table->mut_forks[p->left]);
    p->table->forks[p->left] = 0;
    pthread_mutex_unlock(&p->table->mut_forks[p->left]);
    pthread_mutex_lock(&p->table->mut_forks[p->right]);
    p->table->forks[p->right] = 0;
    pthread_mutex_unlock(&p->table->mut_forks[p->right]);
    print_status(p, "sleep");
    ft_usleep(p->table->time_to_sleep, p->table);
    is_alive(p);
    print_status(p, "think");
}
void    eat(t_philo *p)
{
    p->is_eating = 1;
    print_status(p, "eat");
    ft_usleep(p->table->time_to_eat, p->table);
    p->time_limit = get_time(p->table) + p->table->time_to_die;
    p->is_eating = 0;
    p->eat_count++;
    pthread_mutex_lock(&p->table->mut_forks[p->left]);
    p->table->forks[p->left] = 0;
    pthread_mutex_unlock(&p->table->mut_forks[p->left]);
    pthread_mutex_lock(&p->table->mut_forks[p->right]);
    p->table->forks[p->right] = 0;
    pthread_mutex_unlock(&p->table->mut_forks[p->right]);
    p->table->done++;
}
void    take_forks(t_philo *p)
{
    int i;
    int fork;
    
    i = 0;
    while (i < 2)
    {
        is_alive(p);
        if (i == 0)
            fork = p->left;
        else if (i == 1)
            fork = p->right;
        pthread_mutex_lock(&p->table->mut_forks[fork]);
        if (p->table->forks[fork] == 0)
        {
            print_status(p,"fork");
            p->table->forks[fork] = 1;
            i++;
        }
        pthread_mutex_unlock(&p->table->mut_forks[fork]);
    }
}

void    *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *) arg;
    while(1)
    {
        take_forks(p);
        eat(p);
        if (p->eat_count == p->table->meals_to_eat)
        {
            print_status(p, "finish");
            ft_free_no_message(p->table);
        }
        drop_forks(p);
    }
    return NULL;
}
