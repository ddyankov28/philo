/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:36:34 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/13 10:11:23 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	int			eat_count;
	int			done;
	long long	last_eat;
	pthread_t	thread;
	struct s_struct	*table;
}				t_philo;

typedef struct s_struct
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_to_eat;
	int			dead;
	int			*forks;
	long long	start_time;
	t_philo		*philo;
	pthread_mutex_t mut_print;
	pthread_mutex_t mut_dead;
	pthread_mutex_t *mut_forks;
}				t_struct;
/* frees */
void			ft_free(t_struct *table, char *message);
void			ft_free_no_message(t_struct *table);


void			*routine(void *arg);
void			set_mutexes(t_struct *table);
void			create_threads(t_struct *table);

/* utils */
int	ft_atoi(const char *str, t_struct *table);
int	ft_strcmp(char *s1, char *s2);
long long	get_time(t_struct *table);
int			time_update(long long time_to_pass, t_struct *table);
void    one_philo_thread(t_struct *table);
int		ft_strcmp(char *s1, char *s2);

void    print_status(t_philo *p, char *status);
int     is_alive(t_philo *p);
void		fifth_argument(t_struct *table);

#endif