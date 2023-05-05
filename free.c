/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:57 by ddyankov          #+#    #+#             */
/*   Updated: 2023/05/04 17:21:05 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_free(t_struct *table, char *message)
{
    printf("%s\n", message);
    if (table)
        free(table);
    exit(1);
}
void    ft_free_no_message(t_struct *table)
{
    if (table)
        free(table);
    exit(1);
}