/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_metadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:04:44 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:24:07 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
}

void	open_semaphores(sem_t **semaphores, int *vars)
{
	sem_unlink(SEM_FORK);
	semaphores[FORK] = sem_open(SEM_FORK, O_CREAT, 0666, vars[NUM_PHILOS]);
	sem_unlink(SEM_READY);
	semaphores[READY] = sem_open(SEM_READY, O_CREAT, 0666, 1);
	sem_unlink(SEM_ISDEAD);
	semaphores[ISDEAD] = sem_open(SEM_ISDEAD, O_CREAT, 0666, 1);
	sem_unlink(SEM_LASTMEAL);
	semaphores[LASTMEAL] = sem_open(SEM_LASTMEAL, O_CREAT, 0666, 1);
}

t_philo	*create_philo_metadatas(int *vars)
{
	sem_t			*semaphores[4];
	t_philo			*result;
	int				i;

	i = 0;
	result = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	if (!result)
	{
		printf("Failed to malloc vars\n");
		return (NULL);
	}
	open_semaphores(semaphores, vars);
	while (i < vars[NUM_PHILOS])
	{
		metadata_init(result, vars, i);
		result[i].forks_sem = semaphores[FORK];
		result[i].is_ready_sem = semaphores[READY];
		result[i].is_alive_sem = semaphores[ISDEAD];
		result[i].last_ate_sem = semaphores[LASTMEAL];
		i++;
	}
	return (result);
}
