/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:36:34 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/29 16:33:49 by ddyankov         ###   ########.fr       */
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
	int				id;
	int				left;
	int				right;
	int				eat_count;
	long long		last_eat;
	pthread_t		thread;
	struct s_struct	*table;
}					t_philo;

typedef struct s_struct
{
	int				num_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				meals_to_eat;
	int				end;
	int				*forks;
	long long		start_t;
	t_philo			*philo;
	pthread_mutex_t	mut_end;
	pthread_mutex_t	*mut_forks;
}					t_struct;

int					ft_atoi(const char *str);
int					time_update(long long time_to_pass, t_struct *table);
int					one_philo_thread(t_struct *table);
int					is_alive(t_philo *p);
long long			get_time(void);
void				ft_free(t_struct *table, char *message);
void				*routine(void *arg);
void				print_status(t_philo *p, char *status);
void				fifth_argument(t_struct *table);
void				lock_forks(t_philo *p, int odd_or_even);
void				unlock_forks(t_philo *p, int odd_or_even);
void				drop_forks(t_philo *p, int odd_or_even);

#endif