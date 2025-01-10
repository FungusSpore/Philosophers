/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_metadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:04:44 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/10 17:59:50 by jianwong         ###   ########.fr       */
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

t_philo	*create_philo_metadatas(int *vars)
{
	t_philo				*result;
	sem_t		*forks_sem;
	sem_t		*is_alive_sem;
	sem_t		*last_meal_sem;
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
	sem_unlink(SEM_LASTMEAL);
	last_meal_sem = sem_open(SEM_LASTMEAL, O_CREAT, 0666, 1);
	while (i < vars[NUM_PHILOS])
	{
		metadata_init(result, vars, i);
		result[i].forks_sem = forks_sem;
		result[i].is_alive_sem = is_alive_sem;
		result[i].last_ate_sem = last_meal_sem;
		i++;
	}
	return (result);
}
