/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:23:56 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/09 22:56:47 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>

int	is_philo_dead(t_philo *metadata)
{
	int	is_dead;

	sem_wait(metadata->is_alive_sem);
	is_dead = metadata->is_dead;
	sem_post(metadata->is_alive_sem);
	if (is_dead)
		return (1);
	return (0);
}

void	philo_grab_fork(sem_t *sem_fork, t_philo *metadata, size_t start)
{
	sem_wait(sem_fork);
	if (is_philo_dead(metadata))
		return ;
	start = get_current_time();
	printf("%lu %d has taken a fork\n", \
	start - metadata->start_time, metadata->index);
}
