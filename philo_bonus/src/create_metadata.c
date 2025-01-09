/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_metadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:04:44 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/09 22:45:31 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

static void	metadata_init(t_philo *result, \
int *vars, int i)
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
}

t_philo	*create_philo_metadatas(int *vars)
{
	t_philo				*result;
	sem_t		*forks_sem;
	sem_t		*is_alive_sem;
	int					i;

	i = 0;
	result = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	if (!result)
	{
		printf("Failed to malloc vars\n");
		return (NULL);
	}
	sem_unlink(SEM_FORK);
	forks_sem = sem_open(SEM_FORK, O_CREAT, 0666, vars[NUM_PHILOS]);
	sem_unlink(SEM_ISDEAD);
	is_alive_sem = sem_open(SEM_ISDEAD, O_CREAT, 0666, 1);
	// int sem_value;
	// sem_getvalue(forks_sem, &sem_value);
	// printf("Semaphore value: %d\n", sem_value);
	// sem_getvalue(is_alive_sem, &sem_value);
	// printf("Semaphore value: %d\n", sem_value);
	while (i < vars[NUM_PHILOS])
	{
		metadata_init(result, vars, i);
		result[i].forks_sem = forks_sem;
		result[i].is_alive_sem = is_alive_sem;
		i++;
	}
	return (result);
}
