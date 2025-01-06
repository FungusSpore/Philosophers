/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_metadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:10:47 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/06 17:56:01 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static pthread_mutex_t	*create_forks(int *vars)
{
	pthread_mutex_t	*result;
	int					i;

	i = 0;
	result = malloc(sizeof(pthread_mutex_t) * vars[NUM_PHILOS]);
	if (!result)
	{
		printf("Failed to allocate memory for forks\n");
		return (NULL);
	}
	while (i < vars[NUM_PHILOS])
		if (pthread_mutex_init(&result[i++], NULL) != 0)
		{
			printf("Failed to init mutex\n");
			free(result);
			return (NULL);
		}
	return (result);
}

t_philo	*create_philo_metadatas(int *vars)
{
	t_philo		*result;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	result = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	if (!result)
		return (NULL);
	forks = create_forks(vars);
	while (i < vars[NUM_PHILOS])
	{
		result[i].index = i + 1;
		result[i].time_die = vars[TIME_DIE];
		result[i].time_eat = vars[TIME_EAT];
		result[i].time_sleep = vars[TIME_SLEEP];
		result[i].min_meals = vars[MIN_MEALS];
		result[i].is_dead = 0;
		result[i].last_ate = -1;
		result[i].left_fork = forks[vars[NUM_PHILOS] - i];
		result[i].right_fork = forks[i];
	}
	return (result);
}
