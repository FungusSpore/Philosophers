/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:33:42 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 17:27:25 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	if (metadata->index % 2 == 1)
	{
		pthread_mutex_lock(metadata->left_fork);
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
		pthread_mutex_lock(metadata->right_fork);
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
	}
	else
	{
		pthread_mutex_lock(metadata->right_fork);
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
		pthread_mutex_lock(metadata->left_fork);
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
	}
}

void	philo_eat(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is eating\n", \
	start - metadata->start_time, metadata->index);
	metadata->last_ate = start;
	usleep(metadata->time_eat * 1000);
	pthread_mutex_unlock(metadata->left_fork);
	pthread_mutex_unlock(metadata->right_fork);
}

void	philo_sleep(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is sleeping\n", \
	start - metadata->start_time, metadata->index);
	usleep(metadata->time_sleep * 1000);
}

void	*philo_routine(void *args)
{
	t_philo	*metadata;

	metadata = (t_philo *)args;
	while (metadata->meals_ate != metadata->min_meals)
	{
		philo_think(metadata);
		philo_eat(metadata);
		philo_sleep(metadata);
		usleep(100);
		if (metadata->min_meals > 0)
			metadata->meals_ate++;
	}
	return (NULL);
}
