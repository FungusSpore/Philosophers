/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:33:42 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 23:56:13 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_philo *metadata)
{
	int	is_dead;

	printf("here\n");
	pthread_mutex_lock(metadata->is_alive_mutex);
	is_dead = metadata->is_dead;
	pthread_mutex_unlock(metadata->is_alive_mutex);
	printf("here\n");
	if (is_dead)
	{
		printf("here\n");
		return (1);
	}
	return (0);
}

void	philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	if (metadata->index % 2 == 1)
	{
		pthread_mutex_lock(metadata->left_fork);
		if (is_philo_dead(metadata))
			return ;
		start = get_current_time();
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
		pthread_mutex_lock(metadata->right_fork);
		if (is_philo_dead(metadata))
			return ;
		printf("%lu %d has taken a fork\n", \
		start - metadata->start_time, metadata->index);
		return ;
	}
	pthread_mutex_lock(metadata->right_fork);
	if (is_philo_dead(metadata))
		return ;
	start = get_current_time();
	printf("%lu %d has taken a fork\n", \
	start - metadata->start_time, metadata->index);
	pthread_mutex_lock(metadata->left_fork);
	if (is_philo_dead(metadata))
		return ;
	printf("%lu %d has taken a fork\n", \
	start - metadata->start_time, metadata->index);
}

void	philo_eat(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is eating\n", \
	start - metadata->start_time, metadata->index);
	metadata->last_ate = start;
	if (metadata->min_meals > 0)
		metadata->meals_ate++;
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
		if (!is_philo_dead(metadata))
			philo_think(metadata);
		if (!is_philo_dead(metadata))
			philo_eat(metadata);
		if (!is_philo_dead(metadata))
			philo_sleep(metadata);
		if (is_philo_dead(metadata))
			break ;
		usleep(100);
	}
	return (NULL);
}
