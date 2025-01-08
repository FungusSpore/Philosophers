/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:48:32 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/08 16:48:40 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_philo *metadata)
{
	int	is_dead;

	pthread_mutex_lock(metadata->is_alive_mutex);
	is_dead = metadata->is_dead;
	pthread_mutex_unlock(metadata->is_alive_mutex);
	if (is_dead)
		return (1);
	return (0);
}

void	philo_grab_fork(pthread_mutex_t *fork, t_philo *metadata, size_t start)
{
	pthread_mutex_lock(fork);
	if (is_philo_dead(metadata))
		return ;
	start = get_current_time();
	printf("%lu %d has taken a fork\n", \
	start - metadata->start_time, metadata->index);
}
