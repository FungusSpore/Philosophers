/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:33:42 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:10:23 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>

static void	*lonely_philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	philo_grab_fork(metadata->left_fork, metadata, start);
	while (1)
	{
		if (metadata->is_dead)
		{
			pthread_mutex_unlock(metadata->left_fork);
			return (NULL);
		}
	}
	return (NULL);
}

static void	philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	usleep(1000);
	philo_grab_fork(metadata->left_fork, metadata, start);
	philo_grab_fork(metadata->right_fork, metadata, start);
	if (metadata->is_dead)
	{
		pthread_mutex_unlock(metadata->left_fork);
		pthread_mutex_unlock(metadata->right_fork);
	}
}

static void	philo_eat(t_philo *metadata)
{
	size_t	start;

	pthread_mutex_lock(metadata->read_last_ate_mutex);
	start = get_current_time();
	printf("%lu %d is eating\n", \
	start - metadata->start_time, metadata->index);
	metadata->last_ate = start;
	if (metadata->min_meals > 0)
		metadata->meals_ate++;
	pthread_mutex_unlock(metadata->read_last_ate_mutex);
	usleep(metadata->time_eat * 1000);
	pthread_mutex_unlock(metadata->left_fork);
	pthread_mutex_unlock(metadata->right_fork);
}

static void	philo_sleep(t_philo *metadata)
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
	pthread_mutex_lock(metadata->is_philo_ready_mutex);
	pthread_mutex_unlock(metadata->is_philo_ready_mutex);
	if (metadata->index % 2 == 1)
		usleep(metadata->time_eat * 900);
	if (metadata->total_philo == 1)
		return (lonely_philo_think(metadata));
	while (metadata->meals_ate != metadata->min_meals)
	{
		if (!is_philo_dead(metadata))
			philo_think(metadata);
		if (!is_philo_dead(metadata))
			philo_eat(metadata);
		if (!is_philo_dead(metadata))
			philo_sleep(metadata);
		if (is_philo_dead(metadata))
			break ;
	}
	return (NULL);
}
