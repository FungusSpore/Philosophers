/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:25:15 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/10 18:03:52 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <semaphore.h>
#include <stdio.h>

static void	*lonely_philo_think(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is thinking\n", \
	start - metadata->start_time, metadata->index);
	philo_grab_fork(metadata->forks_sem, metadata, start);
	while (1)
	{
		if (metadata->is_dead)
		{
			sem_post(metadata->forks_sem);
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
	philo_grab_fork(metadata->forks_sem, metadata, start);
	philo_grab_fork(metadata->forks_sem, metadata, start);
	if (metadata->is_dead)
	{
		sem_post(metadata->forks_sem);
		sem_post(metadata->forks_sem);
	}
}

static void	philo_eat(t_philo *metadata)
{
	size_t	start;

	start = get_current_time();
	printf("%lu %d is eating\n", \
	start - metadata->start_time, metadata->index);
	metadata->last_ate = start;
	sem_wait(metadata->last_ate_sem);
	if (metadata->min_meals > -1)
		metadata->meals_ate++;
	sem_post(metadata->last_ate_sem);
	usleep(metadata->time_eat * 1000);
	sem_post(metadata->forks_sem);
	sem_post(metadata->forks_sem);
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
	if (metadata->index % 2 == 1)
		usleep(metadata->time_eat * 950);
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
		usleep(200);
	}
	return (NULL);
}
