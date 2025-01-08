/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_metadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:10:47 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/08 18:17:08 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_metadata(t_philo *metadatas, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < metadatas->total_philo)
	{
		pthread_mutex_destroy(metadatas[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(metadatas->is_alive_mutex);
	pthread_mutex_destroy(metadatas->is_philo_ready_mutex);
	free(metadatas->is_alive_mutex);
	free(metadatas->is_philo_ready_mutex);
	free(forks);
	free(metadatas);
}

static pthread_mutex_t	*create_forks(int *vars)
{
	pthread_mutex_t	*result;
	int				i;

	i = 0;
	result = malloc(sizeof(pthread_mutex_t) * vars[NUM_PHILOS]);
	if (!result)
	{
		printf("Failed to allocate memory for forks\n");
		return (NULL);
	}
	while (i < vars[NUM_PHILOS])
	{
		if (pthread_mutex_init(&(result[i++]), NULL) != 0)
		{
			printf("Failed to init mutex\n");
			free(result);
			return (NULL);
		}
	}
	return (result);
}

static void	metadata_init(t_philo *result, \
int *vars, pthread_mutex_t *forks, int i)
{
	result[i].index = i + 1;
	result[i].total_philo = vars[NUM_PHILOS];
	result[i].time_die = vars[TIME_DIE];
	result[i].time_eat = vars[TIME_EAT];
	result[i].time_sleep = vars[TIME_SLEEP];
	result[i].min_meals = vars[MIN_MEALS];
	result[i].meals_ate = 0;
	result[i].is_dead = 0;
	result[i].start_time = get_current_time();
	result[i].last_ate = get_current_time();
	result[i].left_fork = &forks[(i + 1) % vars[NUM_PHILOS]];
	result[i].right_fork = &forks[i];
}

static int	malloc_vars(t_philo **result, pthread_mutex_t **is_alive_mutex, \
pthread_mutex_t **is_philo_ready_mutex, int *vars)
{
	*result = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	if (!*result)
		return (1);
	*is_alive_mutex = malloc(sizeof(pthread_mutex_t));
	if (!*is_alive_mutex)
	{
		free(*result);
		return (1);
	}
	*is_philo_ready_mutex = malloc(sizeof(pthread_mutex_t));
	if (!*is_philo_ready_mutex)
	{
		free(*is_alive_mutex);
		free(*result);
		return (1);
	}
	return (0);
}

t_philo	*create_philo_metadatas(int *vars, pthread_mutex_t **forks)
{
	pthread_mutex_t		*is_alive_mutex;
	pthread_mutex_t		*is_philo_ready_mutex;
	t_philo				*result;
	int					i;

	i = 0;
	if (malloc_vars(&result, &is_alive_mutex, &is_philo_ready_mutex, vars))
	{
		printf("Failed to malloc vars\n");
		return (NULL);
	}
	*forks = create_forks(vars);
	if (!*forks)
		return (NULL);
	pthread_mutex_init(is_alive_mutex, NULL);
	pthread_mutex_init(is_philo_ready_mutex, NULL);
	while (i < vars[NUM_PHILOS])
	{
		metadata_init(result, vars, *forks, i);
		result[i].is_alive_mutex = is_alive_mutex;
		result[i].is_philo_ready_mutex = is_philo_ready_mutex;
		i++;
	}
	return (result);
}
