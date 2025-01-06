/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:33:42 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 01:35:11 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void	philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	if (metadata->index % 2 == 1)
	{
		pthread_mutex_lock(metadata->left_fork);
		pthread_mutex_lock(metadata->right_fork);
	}
	else
	{
		pthread_mutex_lock(metadata->right_fork);
		pthread_mutex_lock(metadata->left_fork);
	}
}

void	philo_eat(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is eating\n", \
	start - metadata->start_time, metadata->index);
	metadata->last_ate = start;
	usleep(metadata->time_eat);
	pthread_mutex_unlock(metadata->left_fork);
	pthread_mutex_unlock(metadata->right_fork);
}

void	philo_sleep(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is sleeping\n", \
	start - metadata->start_time, metadata->index);
	usleep(metadata->time_sleep);
}

void	*philo_routine(void *args)
{
	t_philo	*metadata;
	int		i;

	metadata = (t_philo *)args;
	i = 0;
	metadata->last_ate = get_current_time();
	metadata->start_time = get_current_time();
	while (i != metadata->min_meals)
	{
		philo_think(metadata);
		philo_eat(metadata);
		philo_sleep(metadata);
		if (metadata->min_meals > 0)
			i++;
	}
	return (NULL);
}
